#include "motion_arduino_adapter.h"

MotionArduinoAdapter::MotionArduinoAdapter(QObject *parent) :
    QObject(parent),
    m_serial(new QSerialPort(this)),
    m_socketHandler(new WebSocketHandler()),
    m_repository(this)
{
    m_serial->setBaudRate(9600);
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(onQSerialPort_ReadyRead()));

    connect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    connect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    connect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        qDebug() << "Name : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        if(info.portName() == m_repository.m_serialPortName)
        {
            qDebug() << "Motion Controller has been found.";
            this->openSerialPort(info);
            break;
        }
    }
}

MotionArduinoAdapter::~MotionArduinoAdapter()
{
    disconnect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    disconnect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    disconnect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));

    delete m_socketHandler;
    if(m_serial->isOpen())
    {
        m_serial->close();
    }
    delete m_serial;
}

Repository &MotionArduinoAdapter::getRepository()
{
    return m_repository;
}


MotionArduinoAdapter &MotionArduinoAdapter::getInstance()
{
    static QScopedPointer<MotionArduinoAdapter> m_instance;
    if(m_instance.data() == nullptr)
    {
        m_instance.reset( new MotionArduinoAdapter() );
    }
    return *m_instance;
}

void MotionArduinoAdapter::openSerialPort(const QSerialPortInfo &info)
{
    m_serial->setPort(info);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "opened" << m_serial->portName();
        emit serialPortOpened();
    }
    else {
        qApp->quit();
    }
}

void MotionArduinoAdapter::onQSerialPort_ReadyRead()
{
    this->m_repository.m_serialPortReadBuffer.append(m_serial->readAll());
    bool ok = false;
    QtJson::parse(QString::fromUtf8(this->m_repository.m_serialPortReadBuffer), ok);
    if(ok)
    {
        this->processMessageFromSerialPort(QString::fromUtf8(this->m_repository.m_serialPortReadBuffer));
        this->m_repository.m_serialPortReadBuffer.clear();
    }
}

void MotionArduinoAdapter::processMessageFromSerialPort(QString message)
{
    bool parsed = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(message, parsed).toMap();
    if(!parsed) return;

    m_repository.updateCurrentState(parsedMessage);
    this->sendStateToServer();
}

void MotionArduinoAdapter::sendStateToServer()
{
    QByteArray data = QtJson::serialize(m_repository.currentState());
    qDebug() << "send to server" << QString::fromUtf8(data);
    qDebug() << " ";
    m_socketHandler->sendBinaryMessage(data);
}

void MotionArduinoAdapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool parsed = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(messageString, parsed).toMap();
    if(!parsed) return;

    QString target = parsedMessage["target"].toString();
    if(target.toLower() != "motioncontroller") return;

    QString action = parsedMessage["action"].toString();
    if(action == "getCurrentState")
    {
        this->sendStateToServer();
        return;
    }

    QtJson::JsonArray blocks = parsedMessage["blocks"].toList();
    if(blocks.length() <= 0)
        return;
    QtJson::JsonObject block = blocks[0].toMap();
    QtJson::JsonObject detailedInfo = block["detailedInfo"].toMap();

    QString gcodesBlockId = detailedInfo["blockId"].toString();
    QtJson::JsonObject axesArguments = detailedInfo["axesArguments"].toMap();
    int feedrate = detailedInfo["feedrate"].toInt();

    QtJson::JsonArray cmds = {};
    for(auto& axis : m_repository.m_axes)
    {
        if(!axesArguments.contains(axis.getId()))
            continue;

        int position = int(round(axesArguments[axis.getId()].toDouble() * 100));
        if(position == axis.getMotor().targetPos())
            continue;

        if(axis.getMotor().isMoving())
        {
            qDebug() << "MotionArduinoAdapter::onWebSocketHandler_BinaryMessageReceived: motor is moving already. Command"
                     << messageString << "is dropped";
            continue;
        }

        cmds.append(axis.getMotor().prepareMotorCmd(position, feedrate));
    }


    for(auto cmd : cmds)
    {
        qDebug() << "execute" << QString::fromUtf8(QtJson::serialize(cmd));
        m_serial->write(QtJson::serialize(cmd));
    }

    this->sendStateToServer();
}

void MotionArduinoAdapter::onWebSocketHandler_Connected()
{
    qDebug() << "Web socket is connected";
    this->sendStateToServer();
}

void MotionArduinoAdapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    qDebug() << "Web socket disconnected with message" << message << "(code" << code << ")";
}

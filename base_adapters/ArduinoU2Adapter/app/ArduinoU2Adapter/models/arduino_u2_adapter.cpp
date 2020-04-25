#include "arduino_u2_adapter.h"

ArduinoU2Adapter::ArduinoU2Adapter(QString portName, QObject *parent) :
    QObject(parent),
    m_settingsManager(SettingsManager()),
    m_serial(new QSerialPort(this)),
    m_serialReadBuffer(QByteArray()),
    m_socketHandler(new WebSocketHandler(m_settingsManager, this)),
    m_axes(QList<Axis>())
{
    this->loadSettings();

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
        if(info.portName() == portName)
        {
            openPort(info);
            break;
        }
    }

    m_axes.append(Axis("X", Motor(0, 1)));
}

ArduinoU2Adapter::~ArduinoU2Adapter()
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

void ArduinoU2Adapter::loadSettings()
{
    try
    {
        //size_t sensorsPackageSize = m_settingsManager.get("Main", "SensorsBufferSize").toUInt();
        //size_t devicesPackageSize = m_settingsManager.get("Main", "DevicesBufferSize").toUInt();
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();
    }
}

void ArduinoU2Adapter::openPort(const QSerialPortInfo &info)
{
    m_serial->setPort(info);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "opened" << m_serial->portName();
        emit portOpened();
    }
}

void ArduinoU2Adapter::onQSerialPort_ReadyRead()
{
    this->m_serialReadBuffer.append(m_serial->readAll());
    bool ok = false;
    QtJson::parse(QString::fromUtf8(this->m_serialReadBuffer), ok);
    if(ok)
    {
        this->processMessageFromSerialPort(QString::fromUtf8(this->m_serialReadBuffer));
        this->m_serialReadBuffer.clear();
    }
}

void ArduinoU2Adapter::processMessageFromSerialPort(QString message)
{
    qDebug() << "from port" << message;
    bool parsed = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(message, parsed).toMap();
    if(!parsed) return;

    int motorId = parsedMessage["motor"].toInt();
    bool isMoving = parsedMessage["isMoving"].toBool();
    int task = parsedMessage["task"].toInt();
    int progress = parsedMessage["progress"].toInt();
    bool taskCompleted = parsedMessage["taskCompleted"].toBool();
    bool invertDirection = parsedMessage["invertedDirection"].toBool();

    for(auto& axis : m_axes)
    {
        if(axis.getMotor().id() != motorId) continue;

        axis.getTask().updateMotorProgress(invertDirection ? -1*progress : progress);
        axis.getMotor().setIsMoving(isMoving);
    }

    this->sendStateToServer();
}

void ArduinoU2Adapter::sendStateToServer()
{
    QtJson::JsonObject message = {};
    QtJson::JsonObject u2State = {};

    int workflowState = 0;
    for(auto axis : m_axes)
    {
        if(axis.getMotor().isMoving())
        {
            workflowState = 1;
            break;
        }
    }

    u2State["workflowState"] = workflowState;
    u2State["lastError"] = 0;
    u2State["axesCount"] = m_axes.length();

    QtJson::JsonArray axesState = {};
    for(auto axis : m_axes)
    {
        axesState.append(axis.currentState());
    }
    u2State["axes"] = axesState;
    message["u2State"] = u2State;

    QByteArray data = QtJson::serialize(message);
    qDebug() << "sendStateToServer" << QString::fromUtf8(data);
    m_socketHandler->sendBinaryMessage(data);
}

void ArduinoU2Adapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool parsed = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(messageString, parsed).toMap();
    if(!parsed) return;

    QString target = parsedMessage["target"].toString();
    if(target.toLower() != "u2") return;

    QString gcodesFrame = parsedMessage["frame"].toString();
    QtJson::JsonObject gcodesDetailedInfo = parsedMessage["detailedInfo"].toMap();

    QString gcodesFrameId = gcodesDetailedInfo["frameId"].toString();
    int axisCount = gcodesDetailedInfo["axesCount"].toInt();
    QtJson::JsonObject axesArguments = gcodesDetailedInfo["axesArguments"].toMap();
    QString feedrate = gcodesDetailedInfo["feedrate"].toString();

    QtJson::JsonArray cmds = {};
    for(auto axis : m_axes)
    {
        if(!axesArguments.contains(axis.getId())) continue;
        qDebug() << axis.getId() << axesArguments[axis.getId()].toDouble();

        double position = axesArguments[axis.getId()].toDouble();
        if(axis.getId().toLower() != "x") continue;

        axis.setTask(position, 30);
        cmds.append(axis.getTask().toJson(axis.getMotor().step()));
    }


    for(auto cmd : cmds)
    {
        qDebug() << "send" << cmd.toMap();
        m_serial->write(QtJson::serialize(cmd));
    }
}

void ArduinoU2Adapter::onWebSocketHandler_Connected()
{
    qDebug() << "Web socket is connected";
}

void ArduinoU2Adapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    qDebug() << "Web socket disconnected with message" << message << "(code" << code << ")";
}

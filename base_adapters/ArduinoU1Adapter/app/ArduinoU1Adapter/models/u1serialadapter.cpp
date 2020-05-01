#include "u1serialadapter.h"

ArduinoU2Adapter::ArduinoU2Adapter(QString portName, QObject *parent) :
    QObject(parent),
    m_settingsManager(SettingsManager()),
    m_serial(new QSerialPort(this)),
    m_socketHandler(new WebSocketHandler(m_settingsManager, this))
    //m_currentState(new U1State(2, 3)),
    //m_previousState(new U1State(2, 3))
{
    this->loadSettings();

    m_serial->setBaudRate(9600);
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(onQSerialPort_ReadyRead()));
    connect(this, SIGNAL(readFromPort(QByteArray)), this, SLOT(onQSerialPort_ReadFromPort(QByteArray)));

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
}

ArduinoU2Adapter::~ArduinoU2Adapter()
{
    disconnect(m_socketHandler, SIGNAL(connected()), this, SLOT(onWebSocketHandler_Connected()));
    disconnect(m_socketHandler, SIGNAL(disconnected(QWebSocketProtocol::CloseCode,QString)), this, SLOT(onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode,QString)));
    disconnect(m_socketHandler, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onWebSocketHandler_BinaryMessageReceived(QByteArray)));

    delete m_previousState;
    delete m_currentState;
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
        size_t sensorsPackageSize = m_settingsManager.get("Main", "SensorsBufferSize").toUInt();
        size_t devicesPackageSize = m_settingsManager.get("Main", "DevicesBufferSize").toUInt();

        m_currentState = new U1State(sensorsPackageSize, devicesPackageSize);
        m_previousState = new U1State(sensorsPackageSize, devicesPackageSize);

        this->printState();
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();

        m_currentState = new U1State();
        m_previousState = new U1State();
    }
}

bool ArduinoU2Adapter::isStateChanged()
{
    qDebug() << "LastError" << m_currentState->getLastError() << "vs" << m_previousState->getLastError();
    qDebug() << "Sensors" << m_currentState->getSensorsState() << "vs" << m_previousState->getSensorsState();
    qDebug() << "Devices" << m_currentState->getDevicesState() << "vs" << m_previousState->getDevicesState();
    return (m_currentState->getSensorsState() != m_previousState->getSensorsState() ||
                m_currentState->getDevicesState() != m_previousState->getDevicesState() ||
                m_currentState->getLastError() != m_previousState->getLastError());
}

void ArduinoU2Adapter::printState()
{
    qDebug() << "New State";
    qDebug() << "Sensors:";
    for(size_t i = 0; i < m_currentState->getSensorsState().size(); i++)
    {
        qDebug() << "byte #" << i << " = " << (int) m_currentState->getSensorsState().operator [](i);
    }
    qDebug() << "Devices:";
    for(size_t i = 0; i < m_currentState->getDevicesState().size(); i++)
    {
        qDebug() << "byte #" << i << " = " << (int) m_currentState->getDevicesState().operator [](i);
    }
    qDebug() << "LastError: " << m_currentState->getLastError();
    qDebug() << "---------" ;
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
    qDebug() << "start read";
    QByteArray data;
    while (!m_serial->atEnd())
    {
        QByteArray tmp = m_serial->read(1);
        data.push_back(tmp);
        qDebug() << "read" << tmp;
    }
    qDebug() << "end read";
    emit readFromPort(data);
}

void ArduinoU2Adapter::onQSerialPort_ReadFromPort(QByteArray received)
{
    byte lastErrorCode = byte(received[0]);
    m_currentState->setLastError(lastErrorCode);

    // todo: update sensors state
    byte_array sensorsTmp;
    /*for(size_t i = 0; i < m_currentState->getSensorsState().size(); i++)
    {
        sensorsTmp.push_back(received[0]);
    }*/

    for(int i = 1; i < received.size() - 3; i++)
    {
        sensorsTmp.push_back(byte(received[i]));
    }


    qDebug() << "update sensors state" << sensorsTmp;
    m_currentState->setSensorsState(sensorsTmp);

    byte_array devicesTmp;
    devicesTmp.push_back(received[received.size() - 3]);
    devicesTmp.push_back(received[received.size() - 2]);
    devicesTmp.push_back(received[received.size() - 1]);

    qDebug() << "update devices state" << devicesTmp;
    m_currentState->setDevicesState(devicesTmp);
    if(isStateChanged())
    {
        printState();
        this->sendStateToServer(m_currentState);
        m_previousState->setLastError(m_currentState->getLastError());
        m_previousState->setDevicesState(m_currentState->getDevicesState());
        m_previousState->setSensorsState(m_currentState->getSensorsState());
    }
}

void ArduinoU2Adapter::switchDevice(byte_array data)
{
    QByteArray devicesMask;
    devicesMask.push_back(data[1]);
    qDebug() << devicesMask;
    m_serial->write(devicesMask);
}

void ArduinoU2Adapter::switchDevice(size_t index, QString target, QString type)
{
    byte indexByte = 0xff;
    switch (index) {
    case 0:
        indexByte = 0x00;
        break;
    case 1:
        indexByte = 0x01;
        break;
    case 2:
        indexByte = 0x02;
        break;
    default:
        break;
    }

    if(type.toLower() == "spindel")
    {
        if(target.toLower() == "on")
        {
            QByteArray message;
            byte paramsByte = 0x00;
            message.push_back(SWITCH_DEVICE_ON);
            message.push_back(indexByte);
            message.push_back(paramsByte);
            qDebug() << "U1SerialAdapter::switchDevice: on"<< message;
            m_serial->write(message);
        }
        else
        {
            if(target.toLower() == "off")
            {
                QByteArray message;
                byte paramsByte = 0x00;
                message.push_back(SWITCH_DEVICE_OFF);
                message.push_back(indexByte);
                message.push_back(paramsByte);
                qDebug() << "U1SerialAdapter::switchDevice: off"<< message;
                m_serial->write(message);
            }
        }
    }
}

void ArduinoU2Adapter::getCurrentState()
{
    QByteArray message;
    message.push_back(GET_CURRENT_STATE);
    qDebug() << "U1SerialAdapter::getCurrentState:" << message;
    m_serial->write(message);
}

void ArduinoU2Adapter::sendStateToServer(U1State *state)
{
    QtJson::JsonObject message;
    QtJson::JsonObject u1State;

    QtJson::JsonArray sensorsState;
    for(auto item : state->getSensorsState())
    {
        sensorsState.append(item);
    }

    QtJson::JsonArray devicesState;
    for(byte item : state->getDevicesState())
    {
        devicesState.append(item);
    }

    int lastError = state->getLastError();

    u1State["sensors_state"] = sensorsState;
    u1State["devices_state"] = devicesState;
    u1State["last_error"] = lastError;
    u1State["workflow_state"] = 0;
    message["u1_state"] = u1State;

    QByteArray data = QtJson::serialize(message);
    m_socketHandler->sendBinaryMessage(data);
}

void ArduinoU2Adapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool parsed = false;
    QtJson::JsonObject parsedMessage = QtJson::parse(messageString, parsed).toMap();
    if(!parsed) return;

    QString target = parsedMessage["target"].toString();
    if(target.toLower() == "u1")
    {
        QString action = parsedMessage["action"].toString();
        if(action == "switch_device")
        {
            QtJson::JsonObject switchParams = parsedMessage["params"].toMap();
            if(!switchParams.empty())
            {
                size_t index = switchParams["uid"].toUInt();
                QString target = switchParams["target"].toString();
                QString type = switchParams["type"].toString();
                this->switchDevice(index, target, type);
                return;
            }
        }

        if(action == "getCurrentState")
        {
            this->getCurrentState();
            return;
        }
    }
    else
    {
        qDebug() << "U1SerialAdapter::onWebSocketHandler_BinaryMessageReceived: message ignored" << messageString;
    }
}

void ArduinoU2Adapter::sendTestPackageToServer()
{
    this->sendStateToServer(m_currentState);
}

void ArduinoU2Adapter::onWebSocketHandler_Connected()
{
    qDebug() << "Web socket is connected";
    this->sendTestPackageToServer();
}

void ArduinoU2Adapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    qDebug() << "Web socket disconnected with message" << message << "(code" << code << ")";
}

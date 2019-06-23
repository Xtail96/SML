#include "u1serialadapter.h"

U1SerialAdapter::U1SerialAdapter(QString portName, QObject *parent) :
    QObject(parent),
    m_settingsManager(SettingsManager()),
    m_serial(new QSerialPort(this)),
    m_socketHandler(new WebSocketHandler(m_settingsManager, this))
    //m_currentState(new U1State(2, 3)),
    //m_previousState(new U1State(2, 3))
{
    loadSettings();

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

U1SerialAdapter::~U1SerialAdapter()
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

void U1SerialAdapter::loadSettings()
{
    try
    {
        size_t sensorsPackageSize = m_settingsManager.get("General", "SensorsBufferSize").toUInt();
        size_t devicesPackageSize = m_settingsManager.get("General", "DevicesBufferSize").toUInt();

        m_currentState = new U1State(sensorsPackageSize, devicesPackageSize);
        m_previousState = new U1State(sensorsPackageSize, devicesPackageSize);
    }
    catch(std::invalid_argument e)
    {
        qDebug() << e.what();

        m_currentState = new U1State();
        m_previousState = new U1State();
    }
}

bool U1SerialAdapter::isStateChanged()
{
    qDebug() << "LastError" << m_currentState->getLastError() << "vs" << m_previousState->getLastError();
    qDebug() << "Sensors" << m_currentState->getSensorsState() << "vs" << m_previousState->getSensorsState();
    qDebug() << "Devices" << m_currentState->getDevicesState() << "vs" << m_previousState->getDevicesState();
    return (m_currentState->getSensorsState() != m_previousState->getSensorsState() ||
                m_currentState->getDevicesState() != m_previousState->getDevicesState() ||
                m_currentState->getLastError() != m_previousState->getLastError());
}

void U1SerialAdapter::printState()
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

void U1SerialAdapter::openPort(const QSerialPortInfo &info)
{
    m_serial->setPort(info);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "opened" << m_serial->portName();
        emit portOpened();
    }
}

void U1SerialAdapter::onQSerialPort_ReadyRead()
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

void U1SerialAdapter::onQSerialPort_ReadFromPort(QByteArray received)
{
    byte lastErrorCode = received[0];
    m_currentState->setLastError(lastErrorCode);

    // todo: update sensors state
    byte_array sensorsTmp;
    /*for(size_t i = 0; i < m_currentState->getSensorsState().size(); i++)
    {
        sensorsTmp.push_back(received[0]);
    }*/

    for(int i = 1; i < received.size() - 3; i++)
    {
        sensorsTmp.push_back(received[i]);
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
        sendCurrentStateToServer(m_currentState);
        m_previousState->setLastError(m_currentState->getLastError());
        m_previousState->setDevicesState(m_currentState->getDevicesState());
        m_previousState->setSensorsState(m_currentState->getSensorsState());
    }
}

void U1SerialAdapter::switchDevice(byte_array data)
{
    QByteArray devicesMask;
    devicesMask.push_back(data[1]);
    qDebug() << devicesMask;
    m_serial->write(devicesMask);
}

void U1SerialAdapter::switchDevice(size_t index, QString target, QString type)
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


    if(type == "Spindel")
    {
        if(target == "On")
        {
            QByteArray message;
            byte paramsByte = 0x00;
            message.push_back(SWITCH_DEVICE_ON);
            message.push_back(indexByte);
            message.push_back(paramsByte);
            qDebug() << "switch on message"<< message;
            m_serial->write(message);
        }
        else
        {
            if(target == "Off")
            {
                QByteArray message;
                byte paramsByte = 0x00;
                message.push_back(SWITCH_DEVICE_OFF);
                message.push_back(indexByte);
                message.push_back(paramsByte);
                qDebug() << "switch off message"<< message;
                m_serial->write(message);
            }
        }
    }
}

void U1SerialAdapter::sendCurrentStateToServer(U1State *state)
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
    message["u1_state"] = u1State;

    QByteArray data = QtJson::serialize(message);
    m_socketHandler->sendBinaryMessage(data);
}

void U1SerialAdapter::onWebSocketHandler_BinaryMessageReceived(QByteArray message)
{
    QString messageString = QString::fromUtf8(message);
    bool ok = false;
    QtJson::JsonObject result = QtJson::parse(messageString, ok).toMap();
    if(ok)
    {
        QtJson::JsonObject u1Message = result["MessageToU1"].toMap();
        if(!u1Message.empty())
        {
            QtJson::JsonObject switchParams = u1Message["SwitchDevice"].toMap();
            if(!switchParams.empty())
            {
                size_t index = switchParams["Index"].toUInt();
                QString target = switchParams["Target"].toString();
                QString type = switchParams["Type"].toString();
                switchDevice(index, target, type);
                /*byte_array data;
                for(auto param : switchParams)
                {
                    data.push_back(param.toUInt());
                }
                switchDevice(data);*/
            }

            QString directMessage = u1Message["DirectMessage"].toString();
            if(!directMessage.isEmpty())
            {
                if(directMessage == "GetState")
                {
                    qDebug() << "get state";
                    sendCurrentStateToServer(m_currentState);
                }
            }

        }
        else
        {
            qDebug() << "Message ignored";
        }
    }
}

void U1SerialAdapter::sendTestPackageToServer()
{
    sendCurrentStateToServer(m_currentState);
}

void U1SerialAdapter::onWebSocketHandler_Connected()
{
    qDebug() << "Web socket is connected";
    sendTestPackageToServer();
}

void U1SerialAdapter::onWebSocketHandler_Disconnected(QWebSocketProtocol::CloseCode code, QString message)
{
    qDebug() << "Web socket disconnected with message" << message << "(code" << code << ")";
}

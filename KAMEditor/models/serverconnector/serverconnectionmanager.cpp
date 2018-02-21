#include "serverconnectionmanager.h"

ServerConnectionManager::ServerConnectionManager(SettingsManager *sm, bool debug, QObject *parent) :
    QObject(parent),
    m_webSocket(nullptr),
    m_debug(debug)
{
    if(sm == nullptr)
    {
        qDebug() << "new SettingsManager instance in server connection manager";
        sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
    else
    {
        setup(sm);
    }
}

ServerConnectionManager::~ServerConnectionManager()
{
    // Отключаем сокет
    closeWebSocket();

    delete m_webSocket;
    delete m_u1CurrentState;
}

void ServerConnectionManager::setup(SettingsManager *sm)
{
    try
    {
        m_u1CurrentState = new U1State(16, 1);
        m_url = QUrl(sm->get("MachineToolInformation", "ServerUrl").toString());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу! ") + QString(e.what())).exec();
    }
}

void ServerConnectionManager::openWebSocket()
{
    if(!m_url.isEmpty())
    {
        if(m_debug)
        {
            qDebug() << "WebSocket Server url is" << m_url.toString();
        }

        if(m_webSocket != nullptr)
        {
            m_webSocket->close();
            m_webSocket = nullptr;
        }

        m_webSocket = new QWebSocket();
        connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

        m_webSocket->open(QUrl(m_url));
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка подключения", "Не могу установить связь с сервером!").exec();
    }
}

void ServerConnectionManager::closeWebSocket()
{
    if(m_webSocket != nullptr)
    {
        if(m_debug)
        {
            qDebug() << "Close current socket";
        }
        m_webSocket->close();
    }
}

void ServerConnectionManager::onConnected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket connected";
    }
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)));
    connect(m_webSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessageReceived(QByteArray)));
    m_webSocket->sendTextMessage(QStringLiteral("@SML-client@"));
    emit serverIsConnected();
}

void ServerConnectionManager::onDisconnected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket Server with url = " << m_url.toString() << " is disconnected";
    }
    emit serverIsDisconnected();
}

bool ServerConnectionManager::sendTextMessage(QString message)
{
    bool messageSent = false;
    if(m_webSocket != nullptr)
    {
        m_webSocket->sendTextMessage(message);
        messageSent = true;
    }
    else
    {
        emit serverIsDisconnected(QString("Can not send text message:") + message);
    }
    return messageSent;
}

bool ServerConnectionManager::sendBinaryMessage(QByteArray message)
{
    bool messageSent = false;
    if(m_webSocket != nullptr)
    {
        m_webSocket->sendBinaryMessage(message);
        messageSent = true;
    }
    else
    {
        qDebug() << "Can not send binary message";
        emit serverIsDisconnected(QString("Can not send byte message: ") + QString::fromUtf8(message));
    }
    return messageSent;
}

byte_array ServerConnectionManager::getSensorsState()
{
    return m_u1CurrentState->getSensorsState();
}

byte_array ServerConnectionManager::getDevicesState()
{
    return m_u1CurrentState->getDevicesState();
}

void ServerConnectionManager::setU1CurrentState(byte_array sensorsState, byte_array devicesState)
{
    m_u1CurrentState->setSensorsState(sensorsState);
    m_u1CurrentState->setDevicesState(devicesState);
    emit u1StateIsChanged();
}

void ServerConnectionManager::setU1CurrentState(QList<QVariant> sensorsState, QList<QVariant> devicesState)
{
    byte_array currentSensorsState;
    for(auto group : sensorsState)
    {
        currentSensorsState.push_back(group.toUInt());
    }

    byte_array currentDevicesState;
    for(auto group : devicesState)
    {
        currentDevicesState.push_back(group.toUInt());
    }

    setU1CurrentState(currentSensorsState, currentDevicesState);
}

std::map<std::string, double> ServerConnectionManager::getMachineToolCoordinates()
{
    std::map<std::string, double> tmp;
    tmp.insert(std::make_pair("X", 100));
    tmp.insert(std::make_pair("Y", 200));
    tmp.insert(std::make_pair("Z", 300));

    return tmp;
}

void ServerConnectionManager::onTextMessageReceived(QString message)
{
    if (m_debug)
    {
        //QMessageBox(QMessageBox::Information, "", "Message recieved: " + message).exec();
        qDebug() << "Message received:" << message;
        //emit textMessageReceived(message);
    }
}

void ServerConnectionManager::onBinaryMessageReceived(QByteArray message)
{
    if(m_debug)
    {
        emit binaryMessageReceived(message);
    }

    bool ok;
    QString json = QString::fromUtf8(message);
    QtJson::JsonObject result = QtJson::parse(json, ok).toMap();
    if(ok)
    {
        //qDebug() << "success";
        QtJson::JsonObject u1State = result["U1State"].toMap();
        if(!u1State.isEmpty())
        {
            QList<QVariant> sensorsState = u1State["SensorsState"].toList();
            qDebug() << sensorsState;
            QList<QVariant> devicesState = u1State["DevicesState"].toList();
            qDebug() << devicesState;
            setU1CurrentState(sensorsState, devicesState);
        }

        //QtJson::JsonObject u2State = result["U2State"].toMap();
        //qDebug() << !(u2State.isEmpty());
    }
    else
    {
        qDebug() << "an error is occured";
    }


}

void ServerConnectionManager::setDebug(bool debug)
{
    m_debug = debug;
}

#include "serverconnectionmanager.h"

ServerConnectionManager::ServerConnectionManager(const QUrl &url, SettingsManager *sm, bool debug, QObject *parent) :
    QObject(parent)
{

    setupWebSocket(url, debug);

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
    m_webSocket->close();
    delete m_webSocket;
    delete currentState;
}

void ServerConnectionManager::setup(SettingsManager *sm)
{
    try
    {
        size_t axisesCount = sm->get("MachineToolInformation", "AxisesCount").toUInt();
        currentState = new MachineToolState(axisesCount, 16);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу!") + QString(e.what())).exec();
    }
}

void ServerConnectionManager::setupWebSocket(const QUrl &url, bool debug)
{
    m_url = url;
    m_debug = debug;
    if(m_debug)
    {
        qDebug() << "WebSocket Server url is" << m_url.toString();
    }

    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    m_webSocket->open(QUrl(m_url));
}


byte_array ServerConnectionManager::getSensorsState()
{
    return currentState->sensorsState.getSensorsState();
}

void ServerConnectionManager::setSensorsState(byte_array value)
{
    currentState->sensorsState.setSensorsState(value);
    emit machineToolStateIsChanged();
}

std::map<std::string, double> ServerConnectionManager::getMachineToolCoordinates()
{
    return currentState->axisesState.getAxisesCoordinates();
}

void ServerConnectionManager::onConnected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket connected";
    }
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)));
    m_webSocket->sendTextMessage(QStringLiteral("Hello, world!"));
}

void ServerConnectionManager::onDisconnected()
{
    if(m_debug)
    {
        qDebug() << "WebSocket Server with url = " << m_url.toString() << " is disconnected";
    }
}

void ServerConnectionManager::onTextMessageReceived(QString message)
{
    if (m_debug)
    {
        qDebug() << "Message received:" << message;
    }
}

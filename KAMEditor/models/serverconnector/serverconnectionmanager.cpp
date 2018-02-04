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
    connect(m_webSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessageReceived(QByteArray)));
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
    QStringList list = QStringList(message);
    QJsonArray machineToolState = QJsonArray::fromStringList(list);
    if (m_debug)
    {
        //QMessageBox(QMessageBox::Information, "", "Message recieved " + message).exec();
        //qDebug() << "Message received:" << machineToolState;
        //emit textMessageReceived(message);
    }
}

void ServerConnectionManager::onBinaryMessageReceived(QByteArray message)
{
    QJsonDocument document = QJsonDocument::fromJson(message);
    QJsonObject jsonResponse =  document.object();
    qDebug() << "Received binary message" << message << "to json-object:"
             << jsonResponse;

    emit textMessageReceived(QString::fromUtf8(message));
}

void ServerConnectionManager::sendTextMessage(QString message)
{
    m_webSocket->sendTextMessage(message);
}

void ServerConnectionManager::sendBinaryMessage(QByteArray message)
{
    m_webSocket->sendBinaryMessage(message);
}

void ServerConnectionManager::setDebug(bool debug)
{
    m_debug = debug;
}

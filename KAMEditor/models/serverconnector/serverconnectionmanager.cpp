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
    if(!stopServer())
    {
        QMessageBox(QMessageBox::Warning,
                    "Ошибка",
                    "По каким-то причинам сервер не смог самостоятельно завершить работу."
                    "Пожалуйста, откройте диспетчер задач и закройте его вручную.").exec();
    }

    if(m_webSocket != nullptr)
    {
        m_webSocket->close();
        delete m_webSocket;
    }

    delete currentState;
}

void ServerConnectionManager::setup(SettingsManager *sm)
{
    try
    {
        size_t axisesCount = sm->get("MachineToolInformation", "AxisesCount").toUInt();
        currentState = new MachineToolState(axisesCount, 16);

        m_url = QUrl(sm->get("MachineToolInformation", "ServerUrl").toString());
        serverApplicationLocation = sm->get("MachineToolInformation", "ServerLocation").toString();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу! ") + QString(e.what())).exec();
    }
}

bool ServerConnectionManager::startServer()
{
    bool serverStarted = false;
    if(m_webSocket != nullptr)
    {
        system(serverApplicationLocation.toStdString().data());
        serverStarted = true;
    }
    return serverStarted;
}

bool ServerConnectionManager::stopServer()
{
    qDebug() << "stop server";
    bool serverStopped = false;
    if(m_webSocket != nullptr)
    {
        QByteArray closeCommand = QString("close").toUtf8();
        sendBinaryMessage(closeCommand);
        serverStopped = true;
        emit serverIsDisconnected(m_url.toString() + QString(" is disconnected by order"));
    }
    else
    {
        serverStopped = true;
        emit serverIsDisconnected(m_url.toString() + QString(" is not accessable"));
    }
    return serverStopped;
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

void ServerConnectionManager::openWebSocket()
{
    //startServer();
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

void ServerConnectionManager::onTextMessageReceived(QString message)
{
    if (m_debug)
    {
        QMessageBox(QMessageBox::Information, "", "Message recieved: " + message).exec();
        //qDebug() << "Message received:" << machineToolState;
        //emit textMessageReceived(message);
    }
}

void ServerConnectionManager::onBinaryMessageReceived(QByteArray message)
{
    QJsonDocument document = QJsonDocument::fromJson(message);
    QJsonObject jsonResponse =  document.object();

    if(m_debug)
    {
        qDebug() << "Received binary message" << message << "to json-object:"
                 << jsonResponse;

        emit binaryMessageReceived(message);
    }
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
        emit serverIsDisconnected(QString("Can not send byte message: ") + QString::fromUtf8(message));
    }
    return messageSent;
}

void ServerConnectionManager::setDebug(bool debug)
{
    m_debug = debug;
}

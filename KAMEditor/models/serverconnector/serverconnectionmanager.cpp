#include "serverconnectionmanager.h"

ServerConnectionManager::ServerConnectionManager(SettingsManager *sm, bool debug, QObject *parent) :
    QObject(parent),
    m_server(new QProcess()),
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

    if(!startServer())
    {
        QMessageBox(QMessageBox::Information, "Информация",
                    "Не могу запустить сервер! Пожалуйста проверьте конфигурационный файл.").exec();
    }
}

ServerConnectionManager::~ServerConnectionManager()
{
    // Отключаем сокет
    closeWebSocket();

    // Завершаем процесс сервер
    int exitCode = stopServer();
    qDebug() << "Сервер завершил работу с кодом" << exitCode;

    delete m_webSocket;
    delete m_server;
    delete currentState;
}

void ServerConnectionManager::setup(SettingsManager *sm)
{
    try
    {
        size_t axisesCount = sm->get("MachineToolInformation", "AxisesCount").toUInt();
        currentState = new MachineToolState(axisesCount, 16);

        m_url = QUrl(sm->get("MachineToolInformation", "ServerUrl").toString());
        m_serverApplicationLocation = sm->get("MachineToolInformation", "ServerLocation").toString();

        //connect(m_server, SIGNAL(started()), this, SLOT(openWebSocket()));
        //connect(m_server, SIGNAL(finished(int)), this, SLOT(closeWebSocket()));
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу! ") + QString(e.what())).exec();
    }
}

bool ServerConnectionManager::startServer()
{
    bool serverStarted = false;
    QStringList arguments;
    m_server->start(m_serverApplicationLocation, arguments);
    if(m_server->isOpen())
    {
        serverStarted = true;
        if(m_debug)
        {
            qDebug() << "Server" << m_serverApplicationLocation << "with url =" << m_url << "is started";
        }
    }
    else
    {
        if(m_debug)
        {
            qDebug() << "Can not start server" << m_serverApplicationLocation << "with url =" << m_url;
        }
    }
    return serverStarted;
}

int ServerConnectionManager::stopServer()
{
    m_server->close();
    m_server->waitForFinished(-1);
    return m_server->exitCode();
}

void ServerConnectionManager::openWebSocket()
{
    if(!m_url.isEmpty() && m_server->isOpen())
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
        //QMessageBox(QMessageBox::Information, "", "Message recieved: " + message).exec();
        qDebug() << "Message received:" << message;
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

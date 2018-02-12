#include "serverconnectionmanager.h"

ServerConnectionManager::ServerConnectionManager(SettingsManager *sm, bool debug, QObject *parent) :
    QObject(parent),
    //m_server(new QProcess(this)),
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

    /*if(!startServer())
    {
        QMessageBox(QMessageBox::Information, "Информация",
                    "Не могу запустить сервер! Пожалуйста проверьте конфигурационный файл.").exec();
    }*/
}

ServerConnectionManager::~ServerConnectionManager()
{
    // Завершаем процесс сервер
    //int exitCode = stopServer();
    //qDebug() << "Сервер завершил работу с кодом" << exitCode;

    // Отключаем сокет
    closeWebSocket();

    delete m_webSocket;
    //delete m_server;
    delete currentState;
}

void ServerConnectionManager::setup(SettingsManager *sm)
{
    try
    {
        size_t axisesCount = sm->get("MachineToolInformation", "AxisesCount").toUInt();
        currentState = new MachineToolState(axisesCount, 16);

        m_url = QUrl(sm->get("MachineToolInformation", "ServerUrl").toString());
        //m_serverApplicationLocation = sm->get("MachineToolInformation", "ServerLocation").toString();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу! ") + QString(e.what())).exec();
    }
}

/*
bool ServerConnectionManager::startServer()
{
    bool serverRunning = false;
    QStringList arguments;
    if(m_server->state() == QProcess::ProcessState::NotRunning)
    {
        m_server->start(m_serverApplicationLocation, arguments);
        if(m_server->state() == QProcess::ProcessState::Starting || m_server->state() == QProcess::ProcessState::Running)
        {
            serverRunning = true;
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
    }
    else
    {
        serverRunning = true;
    }
    return serverRunning;
}

int ServerConnectionManager::stopServer()
{
    sendBinaryMessage(QByteArray("close"));
    m_server->waitForFinished(60000);

    qDebug() << m_server->state();
    if(m_server->state() != QProcess::ProcessState::NotRunning)
    {
        m_server->close();
        m_server->waitForFinished(-1);
    }
    qDebug() << m_server->state();
    return m_server->exitCode();
}

*/

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
    //QJsonDocument document = QJsonDocument::fromJson(message);
    //QJsonObject jsonResponse =  document.object();
    if(m_debug)
    {
        /*qDebug() << "Received binary message" << message << "to json-object:"
                 << jsonResponse;*/

        emit binaryMessageReceived(message);
    }

    bool ok;
    QString json = QString::fromUtf8(message);
    QtJson::JsonObject result = QtJson::parse(json, ok).toMap();
    if(ok)
    {
        qDebug() << "success";
        qDebug() << "encoding:" << result["encoding"].toString();
        qDebug() << "plugins:";

        foreach(QVariant plugin, result["plug-ins"].toList()) {
            qDebug() << "  -" << plugin.toString();
        }

        QtJson::JsonObject nested = result["indent"].toMap();
        qDebug() << "length:" << nested["length"].toInt();
        qDebug() << "use_space:" << nested["use_space"].toBool();
    }
    else
    {
        qDebug() << "an error is occured";
    }


}

void ServerConnectionManager::testJsonParser()
{
    QtJson::JsonObject message;
    message["encoding"] = "utf-8";

    QtJson::JsonArray plugins;
    plugins.append("c++");
    plugins.append("python");
    plugins.append("ruby");
    message["plug-ins"] = plugins;

    QtJson::JsonObject indent;
    indent["length"] = 3;
    indent["use_space"] = true;

    message["indent"] = indent;

    QByteArray data = QtJson::serialize(message);
    sendBinaryMessage(data);
}

void ServerConnectionManager::setDebug(bool debug)
{
    m_debug = debug;
}

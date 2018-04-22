#include "smlkameditorserver.h"

SMLKAMEditorServer::SMLKAMEditorServer(SettingsManager *settingsManager, QObject *parent) :
    QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_port(0),
    m_debug(false)
{
    if(settingsManager != nullptr)
    {
        setup(settingsManager);
    }
    else
    {
        SettingsManager* sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
}

SMLKAMEditorServer::~SMLKAMEditorServer()
{
    this->stop();

    QList<QWebSocket *> sockets = m_adapters.sokets();
    for(auto socket : sockets)
    {
        if(socket->isValid())
        {
            disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
            disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
            disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
    }

    delete m_server;
}

void SMLKAMEditorServer::setup(SettingsManager *sm)
{
    connect(m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(m_server, SIGNAL(closed()), this, SLOT(onServerClosed()));
    try
    {
        m_port = sm->get("ServerSettings", "ServerPort").toUInt();
        m_debug = sm->get("ServerSettings", "DebugMode").toInt();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }

}

void SMLKAMEditorServer::start()
{
    if(m_port != 0)
    {
        if (m_server->listen(QHostAddress::Any, m_port))
        {
            if (m_debug)
            {
                qDebug() << "Echoserver listening on port" << m_port;
                qDebug() << m_server->error();
                qDebug() << m_server->errorString();
            }
        }
    }
}

void SMLKAMEditorServer::stop()
{
    if(m_server->isListening())
    {
        m_server->close();
    }
}

void SMLKAMEditorServer::onNewConnection()
{
    QWebSocket *pSocket = m_server->nextPendingConnection();

    connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
    connect(pSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    m_adapters.pushBack(pSocket, Adapter::Undefined);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
    }

}

void SMLKAMEditorServer::sendMessageToU1(QByteArray message)
{
    QWebSocket* socket = m_adapters.socketByType(Adapter::U1Adapter);
    if(socket != nullptr)
    {
        socket->sendBinaryMessage(message);
    }
}

void SMLKAMEditorServer::onServerClosed()
{
    if(m_debug)
    {
        qDebug() << "Server Closed";
        qDebug() << m_server->error();
        qDebug() << m_server->errorString();
    }
    emit u1Disconnected();
    emit u2Disconnected();
}

void SMLKAMEditorServer::onTextMessage(QString message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "Message received:" << message;
    }

    if (pSender)
    {
        if(message == "@SML-U1Adapter@")
        {
            registerConnection(pSender, Adapter::U1Adapter);
            pSender->sendTextMessage("Registered!");
            if(m_debug)
            {
                qDebug() << "U1Adapter registered:" << m_adapters.socketByType(Adapter::U1Adapter) << " " << pSender;
            }
        }
        else
        {
            if(message == "@SML-U2Adapter@")
            {
                registerConnection(pSender, Adapter::U2Adapter);
            }
            else
            {
                pSender->sendTextMessage("Connection aborted");
                pSender->close();
            }
        }

    }
}

void SMLKAMEditorServer::onBinaryMessage(QByteArray message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "Binary Message received:" << message;
    }

    if (pSender)
    {
        byteMessageReceived(message);
    }
}

void SMLKAMEditorServer::socketDisconnected()
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "socketDisconnected:" << pSender;
    }

    if (pSender)
    {
        pSender->close();
        int type = m_adapters.typeBySocket(pSender);
        m_adapters.removeAll(pSender);
        pSender->deleteLater();

        if(type == Adapter::U1Adapter)
        {
            emit u1Disconnected();
        }

        if(type == Adapter::U2Adapter)
        {
            emit u2Disconnected();
        }
    }
}

void SMLKAMEditorServer::registerConnection(QWebSocket *connection, int type)
{
    m_adapters.removeAll(connection);
    m_adapters.pushBack(connection, type);
    switch (type) {
    case Adapter::U1Adapter:
        emit u1Connected();
        break;
    case Adapter::U2Adapter:
        emit u2Connected();
        break;
    default:
        break;
    }

}

QStringList SMLKAMEditorServer::currentAdapters()
{
    return m_adapters.adaptersSettings();
}

size_t SMLKAMEditorServer::port() const
{
    return m_port;
}

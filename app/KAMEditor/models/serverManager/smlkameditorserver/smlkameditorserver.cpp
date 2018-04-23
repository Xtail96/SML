#include "smlkameditorserver.h"

SMLKAMEditorServer::SMLKAMEditorServer(const SettingsManager &settingsManager, QObject *parent) :
    QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_port(0),
    m_debug(false)
{
    setup(settingsManager);
}

SMLKAMEditorServer::~SMLKAMEditorServer()
{
    stop();

    for(auto socket : m_u1Connections)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
                disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
                disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
            }
        }
    }
    qDeleteAll(m_u1Connections.begin(), m_u1Connections.end());

    for(auto socket : m_u2Connections)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
                disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
                disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
            }
        }
    }
    qDeleteAll(m_u2Connections.begin(), m_u2Connections.end());

    for(auto socket : m_unregistered)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
                disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
                disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
            }
        }
    }
    qDeleteAll(m_unregistered.begin(), m_unregistered.end());

}

void SMLKAMEditorServer::setup(const SettingsManager &sm)
{
    connect(m_server.data(), SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(m_server.data(), SIGNAL(closed()), this, SLOT(onServerClosed()));
    try
    {
        m_port = sm.get("ServerSettings", "ServerPort").toUInt();
        m_debug = sm.get("ServerSettings", "DebugMode").toInt();
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
                qDebug() << "Hello! SML KAMEditor Server is listening port" << m_port;
                qDebug() << m_server->error();
                qDebug() << m_server->errorString();
            }
        }
    }
}

void SMLKAMEditorServer::stop()
{
    qDebug() << "stop server";
    if(m_server->isListening())
    {
        m_server->close();
    }
    qDebug() << "Server successfully stopped. Good Bye!";
}

void SMLKAMEditorServer::onNewConnection()
{
    QWebSocket* pSocket = m_server->nextPendingConnection();

    connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
    connect(pSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    m_unregistered.push_back(pSocket);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
    }

}

void SMLKAMEditorServer::sendMessageToU1(QByteArray message)
{
    for(auto socket : m_u1Connections)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                socket->sendBinaryMessage(message);
            }
        }
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
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "Message received:" << message;
    }

    if (pSender)
    {
        if(message == "@SML-U1Adapter@")
        {
            registerConnection(pSender, SMLKAMEditorServer::U1Adapter);
            pSender->sendTextMessage("Registered!");
        }
        else
        {
            if(message == "@SML-U2Adapter@")
            {
                registerConnection(pSender, SMLKAMEditorServer::U2Adapter);
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
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (pSender)
    {
        if (m_debug)
        {
            qDebug() << "Binary Message received:" << message;
        }
        emit byteMessageReceived(message);
    }
}

void SMLKAMEditorServer::socketDisconnected()
{
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (pSender)
    {
        if (m_debug)
        {
            qDebug() << "socketDisconnected:" << pSender;
        }
        if(m_u1Connections.contains(pSender))
        {
            m_u1Connections.removeAll(pSender);
            emit u1Disconnected();
        }
        else
        {
            if(m_u2Connections.contains(pSender))
            {
                m_u2Connections.removeAll(pSender);
                emit u2Disconnected();
            }
            else
            {
                m_unregistered.removeAll(pSender);
            }
        }

        pSender->deleteLater();
    }
}

void SMLKAMEditorServer::registerConnection(QWebSocket* connection, int type)
{
    switch (type) {
    case SMLKAMEditorServer::U1Adapter:
        m_u1Connections.push_back(connection);
        m_unregistered.removeAll(connection);
        emit u1Connected();
        if(m_debug)
        {
            qDebug() << "U1Adapter registered:" << connection;
        }
        break;
    case SMLKAMEditorServer::U2Adapter:
        m_u2Connections.push_back(connection);
        m_unregistered.removeAll(connection);
        emit u2Connected();
        if(m_debug)
        {
            qDebug() << "U2Adapter registered:" << connection;
        }
        break;
    default:
        break;
    }

    qDebug() << "u1";
    for(auto socket : m_u1Connections)
    {
        qDebug() << socket;
    }

    qDebug() << "unregistered";
    for(auto socket : m_unregistered)
    {
        qDebug() << socket;
    }
}

QStringList SMLKAMEditorServer::currentAdapters()
{
    QStringList settings;

    for(auto socket : m_u1Connections)
    {
        QString localPort = QString::number(socket->localPort());
        QString localAddress = socket->localAddress().toString();

        QString adapterSettingsString =
                QString("Name [U1Adapter] ") +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        settings.push_back(adapterSettingsString);
    }

    for(auto socket : m_u2Connections)
    {
        QString localPort = QString::number(socket->localPort());
        QString localAddress = socket->localAddress().toString();

        QString adapterSettingsString =
                QString("Name [U1Adapter] ") +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        settings.push_back(adapterSettingsString);
    }

    for(auto socket : m_unregistered)
    {
        QString localPort = QString::number(socket->localPort());
        QString localAddress = socket->localAddress().toString();

        QString adapterSettingsString =
                QString("Name [U1Adapter] ") +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        settings.push_back(adapterSettingsString);
    }

    return settings;
}

size_t SMLKAMEditorServer::port() const
{
    return m_port;
}

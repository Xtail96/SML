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
    this->stop();

    for(size_t i = 0; i < (size_t) m_u1Connections.size(); i++)
    {
        if(m_u1Connections[i]->isValid())
        {
            disconnect(m_u1Connections[i].get(), SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
            disconnect(m_u1Connections[i].get(), SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
            disconnect(m_u1Connections[i].get(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
    }

    for(size_t i = 0; i < (size_t) m_u2Connections.size(); i++)
    {
        if(m_u2Connections[i]->isValid())
        {
            disconnect(m_u2Connections[i].get(), SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
            disconnect(m_u2Connections[i].get(), SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
            disconnect(m_u2Connections[i].get(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
    }

    for(size_t i = 0; i < (size_t) m_unregistered.size(); i++)
    {
        if(m_unregistered[i]->isValid())
        {
            disconnect(m_unregistered[i].get(), SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
            disconnect(m_unregistered[i].get(), SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
            disconnect(m_unregistered[i].get(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
    }
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
                qDebug() << "SML KAMEditor Server listening on port" << m_port;
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
    std::shared_ptr<QWebSocket> pSocket(m_server->nextPendingConnection());

    connect(pSocket.get(), SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
    connect(pSocket.get(), SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
    connect(pSocket.get(), SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    m_unregistered.push_back(pSocket);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
    }

}

void SMLKAMEditorServer::sendMessageToU1(QByteArray message)
{
    for(size_t i = 0; i < (size_t) m_u1Connections.size(); i++)
    {
        if(m_u1Connections[i]->isValid())
        {
            m_u1Connections[i]->sendBinaryMessage(message);
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
    std::shared_ptr<QWebSocket> pSender(qobject_cast<QWebSocket *>(sender()));
    if (m_debug)
    {
        qDebug() << "Message received:" << message;
    }

    if (pSender.get())
    {
        if(message == "@SML-U1Adapter@")
        {
            registerConnection(pSender, SMLKAMEditorServer::U1Adapter);
            pSender->sendTextMessage("Registered!");
            if(m_debug)
            {
                qDebug() << "U1Adapter registered:" << pSender.get();
            }
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
    if (m_debug)
    {
        qDebug() << "Binary Message received:" << message;
    }

    if (pSender)
    {
        emit byteMessageReceived(message);
    }
}

void SMLKAMEditorServer::socketDisconnected()
{
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "socketDisconnected:" << pSender;
    }

    if (pSender)
    {
        pSender->close();

        std::shared_ptr<QWebSocket> socket(pSender);

        if(m_u1Connections.contains(socket))
        {
            m_u1Connections.removeAll(socket);
            emit u1Disconnected();
        }
        else
        {
            if(m_u2Connections.contains(socket))
            {
                m_u2Connections.removeAll(socket);
                emit u2Disconnected();
            }
            else
            {
                m_unregistered.removeAll(socket);
            }
        }

        //pSender->deleteLater();
    }
}

void SMLKAMEditorServer::registerConnection(std::shared_ptr<QWebSocket> connection, int type)
{
    std::shared_ptr<QWebSocket> socket = std::shared_ptr<QWebSocket>(connection.get());
    m_unregistered.removeAll(connection);
    switch (type) {
    case SMLKAMEditorServer::U1Adapter:
        m_u1Connections.push_back(socket);
        emit u1Connected();
        break;
    case SMLKAMEditorServer::U2Adapter:
        m_u2Connections.push_back(socket);
        emit u2Connected();
        break;
    default:
        break;
    }

}

QStringList SMLKAMEditorServer::currentAdapters()
{
    QStringList settings;

    for(size_t i = 0; i < (size_t) m_u1Connections.size(); i++)
    {
        QString localPort = QString::number(m_u1Connections[i]->localPort());
        QString localAddress = m_u1Connections[i]->localAddress().toString();

        QString adapterSettingsString =
                QString("Name [U1Adapter] ") +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        settings.push_back(adapterSettingsString);
    }

    for(size_t i = 0; i < (size_t) m_u2Connections.size(); i++)
    {
        QString localPort = QString::number(m_u2Connections[i]->localPort());
        QString localAddress = m_u2Connections[i]->localAddress().toString();

        QString adapterSettingsString =
                QString("Name [U1Adapter] ") +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        settings.push_back(adapterSettingsString);
    }

    for(size_t i = 0; i < (size_t) m_unregistered.size(); i++)
    {
        QString localPort = QString::number(m_unregistered[i]->localPort());
        QString localAddress = m_unregistered[i]->localAddress().toString();

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

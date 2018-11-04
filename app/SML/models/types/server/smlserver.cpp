#include "smlserver.h"

SMLServer::SMLServer(size_t port, QObject *parent) :
    QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_port(port),
    m_debug(false)
{
    setupConnections();
}

SMLServer::~SMLServer()
{
    stop();
    resetConnections();

    for(auto socket : m_u1Connections)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                QObject::disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
                QObject::disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
                QObject::disconnect(socket, SIGNAL(disconnected()), this, SLOT(onQWebSocket_Disconnected()));
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
                QObject::disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
                QObject::disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
                QObject::disconnect(socket, SIGNAL(disconnected()), this, SLOT(onQWebSocket_Disconnected()));
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
                QObject::disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
                QObject::disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
                QObject::disconnect(socket, SIGNAL(disconnected()), this, SLOT(onQWebSocket_Disconnected()));
            }
        }
    }
    qDeleteAll(m_unregistered.begin(), m_unregistered.end());

}

void SMLServer::setupConnections()
{
    QObject::connect(m_server.data(), SIGNAL(newConnection()), this, SLOT(onQWebSocketServer_NewConnection()));
    QObject::connect(m_server.data(), SIGNAL(closed()), this, SLOT(onQWebSocketServer_Closed()));
}

void SMLServer::resetConnections()
{
    QObject::disconnect(m_server.data(), SIGNAL(newConnection()), this, SLOT(onQWebSocketServer_NewConnection()));
    QObject::disconnect(m_server.data(), SIGNAL(closed()), this, SLOT(onQWebSocketServer_Closed()));
}

void SMLServer::start()
{
    if(m_port != 0)
    {
        if (m_server->listen(QHostAddress::Any, m_port))
        {
            qDebug() << "Hello! SML Server is listening on port" << m_port;
            if (m_debug)
            {
                qDebug() << m_server->error();
                qDebug() << m_server->errorString();
            }
        }
    }
}

void SMLServer::stop()
{
    qDebug() << "stop server";
    if(m_server->isListening())
    {
        m_server->close();
    }
    qDebug() << "Server successfully stopped. Good Bye!";
}

void SMLServer::onQWebSocketServer_NewConnection()
{
    QWebSocket* pSocket = m_server->nextPendingConnection();

    QObject::connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onQWebSocket_TextMessageReceived(QString)));
    QObject::connect(pSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onQWebSocket_BinaryMessageReceived(QByteArray)));
    QObject::connect(pSocket, SIGNAL(disconnected()), this, SLOT(onQWebSocket_Disconnected()));

    m_unregistered.push_back(pSocket);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
    }

}

void SMLServer::sendMessageToU1(QByteArray message)
{
    for(auto socket : m_u1Connections)
    {
        if(socket)
        {
            if(socket->isValid())
            {
                socket->sendBinaryMessage(message);
            }
            else
            {
                throw SynchronizeStateException("WebSocket is invalid");
            }
        }
        else
        {
            throw SynchronizeStateException("WebSocket is null");
        }
    }
}

void SMLServer::onQWebSocketServer_Closed()
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

void SMLServer::onQWebSocket_TextMessageReceived(QString message)
{
    if (m_debug)
    {
        qDebug() << "Message received:" << message;
    }

    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    if(message == "@SML-U1Adapter@")
    {
        try
        {
            registerConnection(pSender, SMLServer::U1Adapter);
            pSender->sendTextMessage("Registered!");
        }
        catch(SynchronizeStateException e)
        {
            qDebug() << e.message();
            emit this->errorOccured(-2);
        }
    }
    else
    {
        if(message == "@SML-U2Adapter@")
        {
            try
            {
                registerConnection(pSender, SMLServer::U2Adapter);
            }
            catch(SynchronizeStateException e)
            {
                qDebug() << e.message();
                emit this->errorOccured(-2);
            }
        }
        else
        {
            pSender->sendTextMessage("Connection aborted");
            pSender->close();
        }
    }
}

void SMLServer::onQWebSocket_BinaryMessageReceived(QByteArray message)
{
    if(m_debug)
    {
        qDebug() << "Binary Message received:" << message;
    }

    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

    if(m_u1Connections.contains(pSender))
    {
        try
        {
            U1State u1 = parseU1BinaryMessage(message);
            emit u1StateChanged(u1.sensors, u1.devices, u1.workflowState, u1.errorCode);
        }
        catch(SynchronizeStateException e)
        {
            qDebug() << e.message();
            emit errorOccured(-3);
        }
    }
}

U1State SMLServer::parseU1BinaryMessage(QByteArray message)
{
    bool ok;
    QString json = QString::fromUtf8(message);
    QtJson::JsonObject result = QtJson::parse(json, ok).toMap();
    if(ok)
    {
        QtJson::JsonObject u1State = result["U1State"].toMap();
        if(!u1State.isEmpty())
        {
            U1State u1;
            u1.sensors = u1State["SensorsState"].toList();
            u1.devices = u1State["DevicesState"].toList();
            u1.errorCode = u1State["LastError"].toInt();
            u1.workflowState = 0;
            return u1;
        }
        else
        {
            throw SynchronizeStateException("empty u1 message");
        }
    }
    else
    {
        throw SynchronizeStateException("an error is occured during parsing json" + QString::fromUtf8(message));
    }
}

void SMLServer::onQWebSocket_Disconnected()
{
    QWebSocket* pSender = qobject_cast<QWebSocket *>(sender());
    if (!pSender) return;

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

void SMLServer::registerConnection(QWebSocket* connection, int type)
{
    if (connection == nullptr)
        throw SynchronizeStateException("Try to Register invalid socket");

    switch (type) {
    case SMLServer::U1Adapter:
        m_u1Connections.push_back(connection);
        m_unregistered.removeAll(connection);
        if(m_debug)
        {
            qDebug() << "U1Adapter registered:" << connection;
        }
        emit u1Connected();
        break;
    case SMLServer::U2Adapter:
        m_u2Connections.push_back(connection);
        m_unregistered.removeAll(connection);
        if(m_debug)
        {
            qDebug() << "U2Adapter registered:" << connection;
        }
        emit u2Connected();
        break;
    default:
        break;
    }

    if(m_debug)
    {
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
}

QStringList SMLServer::currentAdapters()
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

size_t SMLServer::port() const
{
    return m_port;
}

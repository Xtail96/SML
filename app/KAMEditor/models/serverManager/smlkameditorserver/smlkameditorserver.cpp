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

    for(auto socket : m_unregisteredConnections)
    {
        if(socket->isValid())
        {
            disconnect(socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessage(QString)));
            disconnect(socket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(onBinaryMessage(QByteArray)));
            disconnect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
        }
    }
    qDeleteAll(m_unregisteredConnections.begin(), m_unregisteredConnections.end());

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

    m_unregisteredConnections.push_back(pSocket);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
        qDebug() << "Unregistered:" << m_unregisteredConnections;
    }

}

void SMLKAMEditorServer::sendMessageToU1(QByteArray message)
{
    QWebSocket* socket = m_adapters.socketByName(U1Adapter);
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
            registerConnection(pSender, U1Adapter);
            pSender->sendTextMessage("Registered!");
            if(m_debug)
            {
                qDebug() << "U1Adapter registered:" << m_adapters.socketByName(U1Adapter) << " " << pSender;
                qDebug() << "Unregistered:" << m_unregisteredConnections;
            }
        }
        else
        {
            if(message == "@SML-U2Adapter@")
            {
                registerConnection(pSender, U2Adapter);
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
        m_adapters.removeAll(pSender);

        m_unregisteredConnections.removeAll(pSender);
        pSender->deleteLater();
    }
}

void SMLKAMEditorServer::registerConnection(QWebSocket *connection, Role role)
{
    m_adapters.pushBack(connection, role);
    m_unregisteredConnections.removeAll(connection);
    switch (role) {
    case U1Adapter:
        emit u1Connected();
        break;
    case U2Adapter:
        emit u2Connected();
        break;
    default:
        break;
    }

}

QStringList SMLKAMEditorServer::currentAdapters()
{
    QStringList adapters = m_adapters.adaptersSettings();

    for(auto socket : m_unregisteredConnections)
    {
        QString name = "Undefined";
        QString localPort = QString::number(socket->localPort());
        QString localAddress = socket->localAddress().toString();

        QString adapterSettingsString =
                "Name [" + name + "] " +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        adapters.push_back(adapterSettingsString);
    }

    return adapters;
}

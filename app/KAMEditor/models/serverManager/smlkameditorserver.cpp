#include "smlkameditorserver.h"

SMLKAMEditorServer::SMLKAMEditorServer(SettingsManager *settingsManager, QObject *parent) :
    QObject(parent),
    m_server(new QWebSocketServer(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, this)),
    m_port(0),
    m_u1Adapter(nullptr),
    m_u2Adapter(nullptr),
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
    qDeleteAll(m_unregisteredConnections.begin(), m_unregisteredConnections.end());

    if(m_u1Adapter != nullptr)
    {
        m_u1Adapter->deleteLater();
    }

    if(m_u2Adapter != nullptr)
    {
        m_u2Adapter->deleteLater();
    }

    stop();
    m_server->deleteLater();
}

void SMLKAMEditorServer::start()
{
    if(m_port != 0)
    {
        if (m_server->listen(QHostAddress::Any, m_port))
        {
            connect(m_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
            connect(m_server, SIGNAL(closed()), this, SLOT(closeServer()));
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

void SMLKAMEditorServer::sendMessageToU1(QByteArray message)
{
    if(m_u1Adapter != nullptr)
    {
        m_u1Adapter->sendBinaryMessage(message);
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Routing error", "Can not send messae to U1. U1 is empty.").exec();
    }
}

void SMLKAMEditorServer::setup(SettingsManager *sm)
{
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

void SMLKAMEditorServer::closeServer()
{
    if(m_debug)
    {
        qDebug() << "Close Server";
        qDebug() << m_server->error();
        qDebug() << m_server->errorString();
    }
    emit u1Disconnected();
    emit u2Disconnected();
}

void SMLKAMEditorServer::onNewConnection()
{
    QWebSocket *pSocket = m_server->nextPendingConnection();

    connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(processTextMessage(QString)));
    connect(pSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(processBinaryMessage(QByteArray)));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    m_unregisteredConnections.push_back(pSocket);

    if(m_debug)
    {
        qDebug() << "Socket connected:" << pSocket->peerAddress() <<  pSocket->peerName() << pSocket->origin();
        qDebug() << "Unregistered:" << m_unregisteredConnections;
    }

}

void SMLKAMEditorServer::processTextMessage(QString message)
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
                qDebug() << "U1Adapter registered:" << m_u1Adapter << " " << pSender;
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

void SMLKAMEditorServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
    {
        qDebug() << "Binary Message received:" << message;
    }

    if (pSender)
    {
        if(pSender == m_u1Adapter)
        {
            emit byteMessageReceived(message);
        }
        else
        {
            if(pSender == m_u2Adapter)
            {
                emit byteMessageReceived(message);
            }
            else
            {
                pSender->sendTextMessage("Connection aborted");
                pSender->close();
            }
        }
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
        if(pSender == m_u1Adapter)
        {
            m_u1Adapter = nullptr;
            emit u1Disconnected();
        }

        if(pSender == m_u2Adapter)
        {
            m_u2Adapter = nullptr;
            emit u2Disconnected();
        }

        m_unregisteredConnections.removeAll(pSender);
        pSender->deleteLater();
    }
}

void SMLKAMEditorServer::registerConnection(QWebSocket *connection, Role role)
{
    switch (role) {
    case U1Adapter:
        m_u1Adapter = connection;
        emit u1Connected();
        break;
    case U2Adapter:
        m_u2Adapter = connection;
        emit u2Connected();
        break;
    default:
        break;
    }
    m_unregisteredConnections.removeAll(connection);
}

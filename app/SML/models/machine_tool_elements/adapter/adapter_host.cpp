#include "adapter_host.h"

AdapterHost::AdapterHost(quint16 port, QObject *parent) :
    QObject(parent),
    m_server("SMLAdapterServer", QWebSocketServer::NonSecureMode, this),
    m_port(port),
    m_connections(QList<QMetaObject::Connection>())
{
    this->startServer();
}

AdapterHost::~AdapterHost()
{
    this->stopServer();
}

qint64 AdapterHost::sendMessage(QWebSocket *dest, QString message)
{
    if(!dest)
        throw std::invalid_argument("Socket is null");

    if(!dest->isValid())
        throw std::invalid_argument("Invalid socket:" + dest->localAddress().toString().toStdString());


    return dest->sendTextMessage(message);
}

qint64 AdapterHost::sendMessage(QWebSocket *dest, QByteArray message)
{
    if(!dest)
        throw std::invalid_argument("Socket is null");

    if(!dest->isValid())
        throw std::invalid_argument("Invalid socket:" + dest->localAddress().toString().toStdString());

    return dest->sendBinaryMessage(message);
}

quint16 AdapterHost::port() const
{
    return m_port;
}

bool AdapterHost::startServer()
{
    if(m_port == 0)
        throw std::invalid_argument("ivalid port number" + QString(m_port).toStdString());

    if (!m_server.listen(QHostAddress::Any, m_port))
        return false;

    this->setupConnections();

    qDebug() << "Hello! SML Server is listening on port" << m_port;
    return true;
}

void AdapterHost::stopServer()
{
    this->resetConnections();

    qDebug() << "Stop Server";
    if(m_server.isListening())
    {
        m_server.close();
    }
    qDebug() << "Server successfully stopped. Good Bye!";
}

void AdapterHost::setupConnections()
{
    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::newConnection, this, [=](){
        emit this->newConnection(m_server.nextPendingConnection());
    }));

    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::closed, this, [=](){
        emit this->serverStopped();
    }));
}

void AdapterHost::resetConnections()
{
    for(auto& connection : m_connections)
        QObject::disconnect(connection);
}

#include "adapter_server.h"

AdapterServer::AdapterServer(QObject *parent) :
    QObject(parent),
    m_server("SMLAdapterServer", QWebSocketServer::NonSecureMode, this),
    m_port(0),
    m_connections(QList<QMetaObject::Connection>())
{
}

AdapterServer::~AdapterServer()
{
    this->stopServer();
}

quint16 AdapterServer::port() const
{
    return m_port;
}

bool AdapterServer::startServer(quint16 port)
{
    if(m_server.isListening())
        this->stopServer();

    if(port == 0)
        throw std::invalid_argument("ivalid port number" + QString(m_port).toStdString());

    m_port = port;
    if (!m_server.listen(QHostAddress::Any, m_port))
        return false;

    this->setupConnections();

    qDebug() << "Hello! SML Server is listening on port" << m_port;
    return true;
}

void AdapterServer::stopServer()
{
    this->resetConnections();

    qDebug() << "Stop Server";
    if(m_server.isListening())
        m_server.close();
    qDebug() << "Server successfully stopped. Good Bye!";
}

void AdapterServer::setupConnections()
{
    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::newConnection, this, [=](){
        emit this->newConnection(m_server.nextPendingConnection());
    }));

    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::closed, this, [=](){
        emit this->serverStopped();
    }));
}

void AdapterServer::resetConnections()
{
    for(auto& connection : m_connections)
        QObject::disconnect(connection);
}

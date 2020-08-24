#include "adapter_gateway.h"

AdapterGateway::AdapterGateway(QObject *parent) :
    QObject(parent),
    m_server("SMLAdapterGateway", QWebSocketServer::NonSecureMode, this),
    m_port(0),
    m_connections(QList<QMetaObject::Connection>())
{
}

AdapterGateway::~AdapterGateway()
{
    this->close();
}

quint16 AdapterGateway::port() const
{
    return m_port;
}

bool AdapterGateway::open(quint16 port)
{
    if(m_server.isListening())
        this->close();

    if(port == 0)
        throw std::invalid_argument("ivalid port number" + QString(m_port).toStdString());

    m_port = port;
    if (!m_server.listen(QHostAddress::Any, m_port))
        return false;

    this->setupConnections();

    qDebug() << "Hello! Adapter gateway is available on port" << m_port;
    return true;
}

void AdapterGateway::close()
{
    this->resetConnections();


    if(m_server.isListening())
    {
        qDebug() << "Try to close adapter gateway";
        m_server.close();
        qDebug() << "Adapter gateway successfully closed. Good Bye!";
    }
}

void AdapterGateway::setupConnections()
{
    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::newConnection, this, [=](){
        emit this->newConnection(m_server.nextPendingConnection());
    }));

    m_connections.append(QObject::connect(&m_server, &QWebSocketServer::closed, this, [=](){
        emit this->serverStopped();
    }));
}

void AdapterGateway::resetConnections()
{
    for(auto& connection : m_connections)
        QObject::disconnect(connection);
}

#include "websocket_gateway.h"

WebSocketGateway::WebSocketGateway(QObject *parent) :
    QObject(parent),
    m_server("SMLAdapterGateway", QWebSocketServer::NonSecureMode, this),
    m_port(0),
    m_slotsInfo(QList<QMetaObject::Connection>()) {}

WebSocketGateway::~WebSocketGateway()
{
    this->close();
}

quint16 WebSocketGateway::port() const
{
    return m_port;
}

bool WebSocketGateway::isOpen()
{
    return m_server.isListening();
}

bool WebSocketGateway::open(quint16 port)
{
    if(m_server.isListening())
        this->close();

    if(port == 0)
        throw std::invalid_argument("ivalid port number" + QString(m_port).toStdString());

    m_port = port;
    if (!m_server.listen(QHostAddress::Any, m_port))
        return false;

    this->setupSlots();

    qInfo().nospace() << "Hello! Adapter gateway is available on ws://localhost:" << m_port;
    return true;
}

void WebSocketGateway::close()
{
    this->resetSlots();


    if(m_server.isListening())
    {
        qInfo() << "Try to close adapter gateway";
        m_server.close();
        qInfo() << "Adapter gateway successfully closed. Good Bye!";
    }
}

void WebSocketGateway::setupSlots()
{
    m_slotsInfo.append(QObject::connect(&m_server, &QWebSocketServer::newConnection, this, [=](){
        emit this->newConnection(m_server.nextPendingConnection());
    }));

    m_slotsInfo.append(QObject::connect(&m_server, &QWebSocketServer::closed, this, [=](){
        emit this->serverStopped();
    }));
}

void WebSocketGateway::resetSlots()
{
    for(auto& slotInfo : m_slotsInfo)
        QObject::disconnect(slotInfo);
}

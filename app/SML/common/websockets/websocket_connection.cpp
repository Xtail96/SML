#include "websocket_connection.h"

WebSocketConnection::WebSocketConnection(QWebSocket *s):
    m_socket(s)
{
}

WebSocketConnection::~WebSocketConnection()
{
    this->clearSlotsInfo();

    if(m_socket && m_socket->isValid())
    {
        qInfo() << "close socket" << m_socket->peerAddress();
        m_socket->close();
        m_socket->deleteLater();
    }
}

void WebSocketConnection::addSlotInfo(const QMetaObject::Connection &slotInfo)
{
    m_slotsInfo.append(slotInfo);
}

void WebSocketConnection::clearSlotsInfo()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
}

QWebSocket *WebSocketConnection::socket() const
{
    return m_socket;
}

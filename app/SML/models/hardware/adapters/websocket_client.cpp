#include "websocket_client.h"

WebSocketClient::WebSocketClient(QWebSocket *s):
    m_socket(s)
{
}

WebSocketClient::~WebSocketClient()
{
    this->clearSlotsInfo();

    if(m_socket && m_socket->isValid())
    {
        qInfo() << "close socket" << m_socket->peerAddress();
        m_socket->close();
        m_socket->deleteLater();
    }
}

void WebSocketClient::addSlotInfo(const QMetaObject::Connection &slotInfo)
{
    m_slotsInfo.append(slotInfo);
}

void WebSocketClient::clearSlotsInfo()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
}

QWebSocket *WebSocketClient::socket() const
{
    return m_socket;
}

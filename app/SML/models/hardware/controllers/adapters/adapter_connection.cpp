#include "adapter_connection.h"

AdapterConnection::AdapterConnection(QWebSocket *s):
    m_socket(s)
{
}

AdapterConnection::~AdapterConnection()
{
    this->clearSlotsInfo();

    if(m_socket && m_socket->isValid())
    {
        qInfo() << "close socket" << m_socket->peerAddress();
        m_socket->close();
        m_socket->deleteLater();
    }
}

void AdapterConnection::addSlotInfo(const QMetaObject::Connection &slotInfo)
{
    m_slotsInfo.append(slotInfo);
}

void AdapterConnection::clearSlotsInfo()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
}

QWebSocket *AdapterConnection::socket() const
{
    return m_socket;
}

#include "adapter_connection.h"

AdapterConnection::AdapterConnection(QWebSocket *s):
    m_socket(s)
{
}

AdapterConnection::~AdapterConnection()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        qDebug() << "disconnect slot";
        QObject::disconnect(slotInfo);
    }

    if(m_socket && m_socket->isValid())
    {
        qDebug() << "close socket";
        m_socket->close();
        m_socket->deleteLater();
    }
}

void AdapterConnection::addSlotInfo(const QMetaObject::Connection &slotInfo)
{
    m_slotsInfo.append(slotInfo);
}

QWebSocket *AdapterConnection::socket() const
{
    return m_socket;
}

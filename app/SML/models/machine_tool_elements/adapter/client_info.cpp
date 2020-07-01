#include "client_info.h"

ClientInfo::ClientInfo(QWebSocket *s):
    m_socket(s)
{
}

ClientInfo::~ClientInfo()
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

void ClientInfo::addSlotInfo(const QMetaObject::Connection &slotInfo)
{
    m_slotsInfo.append(slotInfo);
}

QWebSocket *ClientInfo::socket() const
{
    return m_socket;
}

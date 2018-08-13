#include "connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    m_connected = false;
}

void Connection::setConnected(bool connected)
{
    if(m_connected != connected)
    {
        m_connected = connected;
        emit this->connectionStateChanged(m_connected);
    }
}

#include "connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    m_connected = false;
    m_lastError = 0;
}

void Connection::setConnected(bool connected)
{
    if(m_connected != connected)
    {
        m_connected = connected;
        emit this->connectionStateChanged(m_connected);
    }
}

void Connection::setLastError(int lastError)
{
    if(m_lastError != lastError)
    {
        m_lastError = lastError;
        emit this->lastErrorChanged(lastError);
    }
}

#include "adapter.h"

Adapter::Adapter(QObject *parent) : QObject(parent)
{
    m_connected = false;
}

void Adapter::setConnected(bool connected)
{
    if(m_connected != connected)
    {
        m_connected = connected;
        emit this->connectionStateChanged(m_connected);
    }
}

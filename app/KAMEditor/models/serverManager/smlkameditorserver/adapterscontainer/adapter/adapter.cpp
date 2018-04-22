#include "adapter.h"

Adapter::Adapter(Role name, QWebSocket *socket) :
    m_name(name),
    m_socket(socket)
{

}

Adapter::~Adapter()
{

}

Role Adapter::name() const
{
    return m_name;
}

QWebSocket *Adapter::socket() const
{
    return m_socket;
}

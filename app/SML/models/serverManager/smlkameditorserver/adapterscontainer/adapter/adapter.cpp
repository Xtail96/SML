#include "adapter.h"

Adapter::Adapter(int name, QWebSocket *socket) :
    m_type(name),
    m_socket(socket)
{

}

Adapter::~Adapter()
{

}

int Adapter::type() const
{
    return m_type;
}

QWebSocket* Adapter::socket() const
{
    return m_socket.data();
}

#include "adapterscontainer.h"

AdaptersContainer::AdaptersContainer()
{

}

AdaptersContainer::~AdaptersContainer()
{
    qDeleteAll(m_adapters.begin(), m_adapters.end());
}

void AdaptersContainer::pushBack(QWebSocket *socket, Role role)
{
    m_adapters.push_back(new Adapter(role, socket));
}

QWebSocket *AdaptersContainer::socketByName(Role name)
{
    QWebSocket* socket = nullptr;
    for(auto adapter : m_adapters)
    {
        if(adapter->name() == name)
        {
            socket = adapter->socket();
            break;
        }
    }
    return socket;
}

Role AdaptersContainer::nameBySocket(QWebSocket *socket)
{
    Role name = Undefined;
    for(auto adapter : m_adapters)
    {
        if(adapter->socket() == socket)
        {
            name = adapter->name();
            break;
        }
    }
    return name;
}

void AdaptersContainer::removeAll(QWebSocket *socket)
{
    QList<Adapter*> tmp;
    for(auto adapter : m_adapters)
    {
        if(adapter->socket() == socket)
        {
            tmp.push_back(adapter);
        }
    }

    for(auto adapter : tmp)
    {
        m_adapters.removeAll(adapter);
    }
}

QList<QWebSocket *> AdaptersContainer::sokets()
{
    QList<QWebSocket *> sockets;
    for(auto adapter : m_adapters)
    {
        sockets.push_back(adapter->socket());
    }
    return sockets;
}

QStringList AdaptersContainer::adaptersSettings()
{
    QStringList adapters;
    for(auto adapter : m_adapters)
    {
        QString name = QString::number(adapter->name());
        QString localPort = QString::number(adapter->socket()->localPort());
        QString localAddress = adapter->socket()->localAddress().toString();

        QString adapterSettingsString =
                "Name [U" + name + "Adapter] " +
                "on local port [" + localPort + "] " +
                "with local address [" + localAddress + "]";
        adapters.push_back(adapterSettingsString);
    }
    return adapters;
}

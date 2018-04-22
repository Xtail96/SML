#include "adapterscontainer.h"

AdaptersContainer::AdaptersContainer()
{

}

AdaptersContainer::~AdaptersContainer()
{
    qDeleteAll(m_adapters.begin(), m_adapters.end());
}

void AdaptersContainer::pushBack(QWebSocket *socket, int type)
{
    if((type != Adapter::U1Adapter) && (type != Adapter::U2Adapter) && (type != Adapter::Undefined))
    {
        type = Adapter::Undefined;
    }
    m_adapters.push_back(new Adapter(type, socket));
}

QWebSocket *AdaptersContainer::socketByType(int type)
{
    QWebSocket* socket = nullptr;
    for(auto adapter : m_adapters)
    {
        if(adapter->type() == type)
        {
            socket = adapter->socket();
            break;
        }
    }
    return socket;
}

int AdaptersContainer::typeBySocket(QWebSocket *socket)
{
    int type = Adapter::Undefined;
    for(auto adapter : m_adapters)
    {
        if(adapter->socket() == socket)
        {
            type = adapter->type();
            break;
        }
    }
    return type;
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
        QString name = QString::number(adapter->type() + 1);
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

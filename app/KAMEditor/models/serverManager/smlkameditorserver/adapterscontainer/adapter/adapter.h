#ifndef ADAPTER_H
#define ADAPTER_H

#include <QString>
#include <QWebSocket>

enum Role {U1Adapter, U2Adapter, Undefined};

class Adapter
{
public:
    explicit Adapter(Role name, QWebSocket *socket);
    ~Adapter();
    Role name() const;
    QWebSocket *socket() const;

protected:
    Role m_name;
    QWebSocket *m_socket;
};

#endif // ADAPTER_H

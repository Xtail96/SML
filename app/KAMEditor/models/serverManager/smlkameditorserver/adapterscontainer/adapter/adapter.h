#ifndef ADAPTER_H
#define ADAPTER_H

#include <QString>
#include <QWebSocket>

class Adapter
{
public:
    enum Type {U1Adapter, U2Adapter, Undefined};

    explicit Adapter(int type, QWebSocket *socket);
    ~Adapter();
    int type() const;
    QWebSocket *socket() const;

protected:
    int m_type;
    QWebSocket *m_socket;
};

#endif // ADAPTER_H

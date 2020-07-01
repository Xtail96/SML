#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QWebSocket>

class ClientInfo
{
public:
    ClientInfo(QWebSocket* s);
    ~ClientInfo();

    void addSlotInfo(const QMetaObject::Connection &slotInfo);

    QWebSocket *socket() const;

private:
    QWebSocket* m_socket;
    QList<QMetaObject::Connection> m_slotsInfo;

};

#endif // CLIENTINFO_H

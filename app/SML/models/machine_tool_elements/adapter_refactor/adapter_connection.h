#ifndef ADAPTERCONNECTION_H
#define ADAPTERCONNECTION_H

#include <QWebSocket>

class AdapterConnection
{
public:
    AdapterConnection(QWebSocket* s);
    ~AdapterConnection();

    void addSlotInfo(const QMetaObject::Connection &slotInfo);

    QWebSocket *socket() const;

private:
    QWebSocket* m_socket;
    QList<QMetaObject::Connection> m_slotsInfo;

};

#endif // ADAPTERCONNECTION_H

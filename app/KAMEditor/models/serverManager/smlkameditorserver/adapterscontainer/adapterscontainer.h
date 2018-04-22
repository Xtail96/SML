#ifndef ADAPTERSCONTAINER_H
#define ADAPTERSCONTAINER_H

#include <QObject>
#include <QList>

#include "models/serverManager/smlkameditorserver/adapterscontainer/adapter/adapter.h"

class AdaptersContainer
{
public:
    explicit AdaptersContainer();
    ~AdaptersContainer();

    void pushBack(QWebSocket* socket, int type);
    QWebSocket* socketByType(int type);
    int typeBySocket(QWebSocket* socket);
    void removeAll(QWebSocket* socket);

    QList<QWebSocket *> sokets();
    QStringList adaptersSettings();

protected:
    QList<Adapter*> m_adapters;
};

#endif // ADAPTERSCONTAINER_H

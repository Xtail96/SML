#ifndef BASEADAPTER_H
#define BASEADAPTER_H

#include <QObject>
#include <QWebSocket>

#include "libs/json_parser/json.h"

#include "models/machine_tool_elements/adapter/client_info.h"

class BaseAdapter : public QObject
{
    Q_OBJECT
public:
    explicit BaseAdapter(QObject *parent = nullptr);
    virtual ~BaseAdapter();

    void addClient(QWebSocket* s);
    void clearClients();

    bool processingTask() const;

protected:
    QList<ClientInfo*> m_clients;
    bool m_processingTask;

    virtual void parseTextMessage(QString message) = 0;
    virtual void parseBinaryMessage(QByteArray message) = 0;

    qint64 sendMessage(QByteArray message);
    void setProcessingTask(bool processingTask);
signals:
    void connectionStateChanged();
    void taskProcessingStateChanged();
};

#endif // BASEADAPTER_H

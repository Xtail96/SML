#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <QWebSocket>

#include "libs/json_parser/json.h"

#include "models/machine_tool_elements/adapter_refactor/adapter_connection.h"

class BaseController : public QObject
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = nullptr);
    virtual ~BaseController();

    void addClient(QWebSocket* s);
    void clearClients();

    bool processingTask() const;
    bool isConnected() const;

protected:
    QList<AdapterConnection*> m_clients;
    bool m_processingTask;

    virtual void parseTextMessage(QString message) = 0;
    virtual void parseBinaryMessage(QByteArray message) = 0;

    qint64 sendMessage(QByteArray message);
    void setProcessingTask(bool processingTask);
signals:
    void connectionStateChanged();
    void taskProcessingStateChanged();
};

#endif // BASECONTROLLER_H

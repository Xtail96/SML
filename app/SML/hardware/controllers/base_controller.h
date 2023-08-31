#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <QTest>

#include "libs/json_parser/json.h"
#include "./task.h"
#include "../../common/websockets/websocket_client.h"


class BaseController : public WebSocketClient
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = nullptr);
    virtual ~BaseController();
    bool isReady() const;
    virtual void startProcessing(Task t) = 0;
    virtual void stopProcessing() = 0;
    virtual void onDisconnected() = 0;
protected:
    QList<QMetaObject::Connection> m_slotsInfo;
    void setTaskProcessing(bool processing);
    void stopProcessing(QString targetControllerId);
private:
    bool m_taskProcessing;
signals:
    /// Состояние обработки задания изменилось.
    void taskProcessingStateChanged();
};

#endif // BASECONTROLLER_H

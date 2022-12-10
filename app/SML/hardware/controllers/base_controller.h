#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <QTest>

#include "libs/json_parser/json.h"
#include "./task.h"
#include "../../common/websockets/websocket_client.h"

/**
 * @brief Базовый контроллер.
 * Содержит код для работы с подключениями через сокеты.
 * Содержит код для получения информации о готовности платы обрабатывать задачи.
 */
class BaseController : public WebSocketClient
{
    Q_OBJECT
public:
    explicit BaseController(QObject *parent = nullptr);
    virtual ~BaseController();
    bool isReady() const;
    virtual void processTask(Task t) = 0;
    virtual void stopProcessing() = 0;
    void setProcessingTask(bool isReady);
    void stopProcessingTask(QString targetControllerId);
    virtual void onDisconnected() = 0;
protected:
    QList<QMetaObject::Connection> m_slotsInfo;

    /// Выполняется ли задача в текущий момент.
    bool m_processingTask;
signals:
    /// Состояние обработки задания изменилось.
    void taskProcessingStateChanged();
};

#endif // BASECONTROLLER_H

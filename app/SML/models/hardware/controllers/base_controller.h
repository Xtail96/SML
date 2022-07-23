#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <QWebSocket>
#include <QTest>

#include "libs/json_parser/json.h"
#include "task.h"
#include "../adapters/websocket_adapter.h"

/**
 * @brief Базовый контроллер.
 * Содержит код для работы с подключениями через сокеты.
 * Содержит код для получения информации о готовности платы обрабатывать задачи.
 */
class BaseController : public WebSocketAdapter
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор  класса.
     * @param parent - родительский объект
     */
    explicit BaseController(QString logName = "", QObject *parent = nullptr);

    /**
     * @brief Деструктор класса.
     */
    virtual ~BaseController();

    /**
     * @brief Возвращает статус обработки задачи.
     * @return Готов ли контроллер к приему новой задачи
     */
    bool isReady() const;


    virtual void processTask(Task t) = 0;
    virtual void stopProcessing() = 0;

protected:

    /// Выполняется ли задача в текущий момент.
    bool m_processingTask;

    /**
     * @brief Устанавливает значение обаработки задачи и испускает сигнал.
     * @param processingTask - обрабатывается ли задача.
     */
    void setProcessingTask(bool isReady);

    void stopProcessingTask(QString targetControllerId);

private:
    QString m_logName;

signals:
    /// Состояние обработки задания изменилось.
    void taskProcessingStateChanged();
};

#endif // BASECONTROLLER_H

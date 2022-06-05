#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <QObject>
#include <QWebSocket>
#include <QTest>

#include "libs/json_parser/json.h"

#include "../controllers/adapters/adapter_connection.h"
#include "task.h"

/**
 * @brief Базовый контроллер.
 * Содержит код для работы с подключениями через сокеты.
 * Содержит код для получения информации о готовности платы обрабатывать задачи.
 */
class BaseController : public QObject
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
     * @brief Добавляет новое подключение адаптера.
     * @warning Добавление происходит только если нет активных подключений.
     * @param s - сокет подключения адаптера
     * @param intialState - начальное состояние контроллера
     */
    void addClient(QWebSocket* s, QtJson::JsonObject intialState);

    /**
     * @brief Очищает список подключенных адаптеров.
     */
    void clearClients();

    /**
     * @brief Возвращает статус обработки задачи.
     * @return Готов ли контроллер к приему новой задачи
     */
    bool isReady() const;

    /**
     * @brief Возвращает статус подключения адаптера.
     * @return Подключен ли адаптер
     */
    bool isConnected() const;

    virtual void processTask(Task t) = 0;
    virtual void stopProcessing() = 0;

protected:
    /// Подключенные адаптеры.
    QList<AdapterConnection*> m_clients;

    /// Выполняется ли задача в текущий момент.
    bool m_processingTask;

    /**
     * @brief Отправляет сообщение на подключенный адаптер.
     * @warning Отправка происходит только на первый адаптер из списка подключений.
     * @param message - сообщение для отправки
     * @return Число отправленных байт информации
     */
    qint64 sendMessage(QByteArray message);

    virtual void setup(QtJson::JsonObject initialState) = 0;

    virtual void newMessageHandler(QtJson::JsonObject msg) = 0;

    /**
     * @brief Устанавливает значение обаработки задачи и испускает сигнал.
     * @param processingTask - обрабатывается ли задача.
     */
    void setProcessingTask(bool isReady);

    void stopProcessingTask(QString targetControllerId);

private:
    QString m_logName;

    /**
     * @brief Обработчик сообщения от адаптера в виде текста.
     * @param message - принятое сообщение от адаптера
     */
    void parseTextMessage(QString message);

    /**
     * @brief Обработчик сообщения от адаптера в виде массива байт.
     * @param message - принятое сообщение от адаптера
     */
    void parseBinaryMessage(QByteArray message);

signals:
    /// Состояние подключения изменилось.
    void connected();

    void disconnected();

    /// Состояние обработки задания изменилось.
    void taskProcessingStateChanged();
};

#endif // BASECONTROLLER_H

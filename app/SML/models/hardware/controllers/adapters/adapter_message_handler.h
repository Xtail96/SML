#ifndef ADAPTERMESSAGEHANDLER_H
#define ADAPTERMESSAGEHANDLER_H

#include <QObject>

#include "libs/json_parser/json.h"

#include "./adapter_connection.h"

class AdapterMessageHandler : public QObject
{
    Q_OBJECT
public:
    explicit AdapterMessageHandler(QObject *parent = nullptr);
    ~AdapterMessageHandler();

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
     * @brief Возвращает статус подключения адаптера.
     * @return Подключен ли адаптер
     */
    bool isConnected() const;

    /**
     * @brief Отправляет сообщение на подключенный адаптер.
     * @warning Отправка происходит только на первый адаптер из списка подключений.
     * @param message - сообщение для отправки
     * @return Число отправленных байт информации
     */
    qint64 sendMessage(QByteArray message);

protected:
    /// Подключенные адаптеры.
    QList<AdapterConnection*> m_clients;

    virtual void newMessageHandler(QtJson::JsonObject msg) = 0;
    virtual void onClientConnected(QtJson::JsonObject initialState) = 0;

private:
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
    void connected();

    void disconnected();
};

#endif // ADAPTERMESSAGEHANDLER_H

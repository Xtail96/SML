#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QWebSocket>


class WebSocketClient
{
public:
    /**
     * @brief Конструктор класса.
     * @param s - сокет подключения
     */
    WebSocketClient(QWebSocket* s);

    /**
     * @brief Деструктор класса.
     */
    ~WebSocketClient();

    /**
     * @brief Добавляет информацию о подключенном слоте.
     * @param slotInfo - мета-информация о подключении сигнала к слоту
     */
    void addSlotInfo(const QMetaObject::Connection &slotInfo);

    void clearSlotsInfo();

    /**
     * @brief Возвращает сокет подключения.
     * @return указатель на сокет
     */
    QWebSocket *socket() const;

private:
    /// Сокет подключения.
    QWebSocket* m_socket;

    /// Мета-инфрмация о всех подключенных слотах.
    QList<QMetaObject::Connection> m_slotsInfo;
};

#endif // WEBSOCKETCLIENT_H

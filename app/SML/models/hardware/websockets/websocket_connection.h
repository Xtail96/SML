#ifndef WEBSOCKETCONNECTION_H
#define WEBSOCKETCONNECTION_H

#include <QWebSocket>


class WebSocketConnection
{
public:
    /**
     * @brief Конструктор класса.
     * @param s - сокет подключения
     */
    WebSocketConnection(QWebSocket* s);

    /**
     * @brief Деструктор класса.
     */
    ~WebSocketConnection();

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

#endif // WEBSOCKETCONNECTION_H

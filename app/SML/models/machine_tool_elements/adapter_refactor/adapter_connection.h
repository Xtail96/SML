#ifndef ADAPTERCONNECTION_H
#define ADAPTERCONNECTION_H

#include <QWebSocket>

/**
 * @brief Мета-информация о подключении адаптера к системе.
 */
class AdapterConnection
{
public:
    /**
     * @brief Конструктор класса.
     * @param s - сокет подключения
     */
    AdapterConnection(QWebSocket* s);

    /**
     * @brief Деструктор класса.
     */
    ~AdapterConnection();

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

#endif // ADAPTERCONNECTION_H

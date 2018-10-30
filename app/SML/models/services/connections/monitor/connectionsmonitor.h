#ifndef CONNECTIONSMONITOR_H
#define CONNECTIONSMONITOR_H

#include <QObject>
#include "models/types/connection/connection.h"


/**
 * @brief Класс Монитор состояния подключений
 *
 * Предназначен для отслеживания состояния подключений в режиме реального времени.
 */
class ConnectionsMonitor : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор класса
     * Связывает каждое подключение с функциями обработчкиками (onU1_ConnectionStateChanged и onU2_ConnectionStateChanged).
     *
     * @param u1 указатель на подключение адаптера контроллера u1, состояние которого требуется отслеживать
     * @param u2 указатель на подключение адаптера контроллера u2, состояние которого требуется отслеживать
     */
    explicit ConnectionsMonitor(Connection* u1, Connection* u2, QObject *parent = nullptr);

protected:

signals:

    /**
     * @brief Сигнал об изменнии состояния подключения адптера u1
     * @param state обновленное состояние подключения
     */
    void u1StateChanged(bool state);

    /**
     * @brief Сигнал об изменнии состояния подключения адптера u2
     * @param state обновленное состояние подключения
     */
    void u2StateChanged(bool state);

protected slots:

    /**
     * @brief Испускает сигнал об изменении состояния подключения адаптера u1
     * @param state обновленное состояние подключения
     */
    void onU1_ConnectionStateChanged(bool state);

    /**
     * @brief Испускает сигнал об изменении состояния подключения адаптера u2
     * @param state обновленное состояние подключения
     */
    void onU2_ConnectionStateChanged(bool state);
};

#endif // CONNECTIONSMONITOR_H

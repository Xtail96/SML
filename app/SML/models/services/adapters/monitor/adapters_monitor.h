#ifndef CONNECTIONSMONITOR_H
#define CONNECTIONSMONITOR_H

#include <QObject>
#include "models/types/adapter/adapter.h"


/**
 * @brief Класс Монитор состояния подключений
 *
 * Предназначен для отслеживания состояния подключений в режиме реального времени.
 */
class AdaptersMonitor : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Конструктор класса
     * Связывает каждое подключение с функциями обработчкиками.
     *
     * @param u1 указатель на подключение адаптера контроллера u1, состояние которого требуется отслеживать
     * @param u2 указатель на подключение адаптера контроллера u2, состояние которого требуется отслеживать
     */
    explicit AdaptersMonitor(Adapter* u1, Adapter* u2, QObject *parent = nullptr);

protected:
    Adapter* m_u1Adapter;
    Adapter* m_u2Adapter;

signals:

    /**
     * @brief Сигнал об изменнии состояния подключения адптеров&
     * @param u1 обновленное состояние подключения адаптера U1.
     * @param u2 обновленное состояние подключения адаптера U2.
     */
    void AdaptersConnectionStateChanged(bool u1, bool u2);

    /**
     * @brief Сигнал об изменнеии состояния заданий на адаптерах
     * @param u1 обновленный код состояния выполнения заний на адаптере U1.
     * @param u2 обновленный код состояния выполнения заданий на адаптере U2.
     */
    void AdaptersWorkflowStateChanged(int u1, int u2);

protected slots:

    /**
     * @brief Обрабатывает согнал об изменении состояния подключения любого из подключенных адаптеров
     * Испускает сигнал об изменении состояния подключения адаптеров.
     * @param state обновленное состояние подключения любого из адаптеров
     */
    void onAdapter_ConnectionStateChanged(Adapter::Type type, bool state);

    /**
     * @brief Обрабатывает согнал об изменении состояния выполнения заданий любого из подключенных адаптеров
     * Испускает сигнал об изменении состояния выполенния заданий на адаптерах
     * @param state обновленный код состояния выполнения заданий
     */
    void onAdapter_WorkflowStateChanged(Adapter::Type type, int state);
};

#endif // CONNECTIONSMONITOR_H

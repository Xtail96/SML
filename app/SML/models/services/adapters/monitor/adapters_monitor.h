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

signals:

    /**
     * @brief Сигнал об изменнии состояния подключения адптера
     */
    void AdapterConnectionStateChanged();

    /**
     * @brief Сигнал об изменнеии состояния заданий на адаптере
     */
    void AdapterWorkflowStateChanged();

protected slots:

    /**
     * @brief Обрабатывает согнал об изменении состояния подключения любого из подключенных адаптеров
     * Испускает сигнал об изменении состояния подключения адаптеров.
     */
    void onAdapter_ConnectionStateChanged();

    /**
     * @brief Обрабатывает согнал об изменении состояния выполнения заданий любого из подключенных адаптеров
     * Испускает сигнал об изменении состояния выполенния заданий на адаптерах.
     */
    void onAdapter_WorkflowStateChanged();
};

#endif // CONNECTIONSMONITOR_H

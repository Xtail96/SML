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
     * @brief Сигнал об изменнии состояния подключения адптера u1
     * @param state обновленное состояние подключения
     */
    void u1AdapterConnectionStateChanged(bool state);

    /**
     * @brief Сигнал об изменнии состояния подключения адптера u2
     * @param state обновленное состояние подключения
     */
    void u2AdapterConnectionStateChanged(bool state);

    /**
     * @brief Сигнал об изменнеии состояния заданий на адаптере u1
     * @param state обновленный код состояния выполнения заданий
     */
    void u1AdapterWorkflowStateChanged(int state);

    /**
     * @brief Сигнал о возникновении ошибки работы адаптера u1
     * @param errorCode код возникшей ошибки
     */
    void u1AdapterErrorIsOccured(int errorCode);

protected slots:

    /**
     * @brief Испускает сигнал об изменении состояния подключения адаптера u1
     * @param state обновленное состояние подключения
     */
    void onU1Adapter_ConnectionStateChanged(bool state);

    /**
     * @brief Испускает сигнал об изменении состояния подключения адаптера u2
     * @param state обновленное состояние подключения
     */
    void onU2Adapter_ConnectionStateChanged(bool state);

    /**
     * @brief Испускает сигнал об изменении состояния выполенния заданий адаптера u1
     * @param state обновленный код состояния выполнения заданий
     */
    void onU1Adapter_WorkflowStateChanged(int state);

    /**
     * @brief Испускает сигнал о возникновении ошибки работы адаптера u1
     * @param errorCode код ошибки
     */
    void onU1Adapter_ErrorIsOccured(int errorCode);
};

#endif // CONNECTIONSMONITOR_H

#ifndef U1STATE_H
#define U1STATE_H

#include <QList>

/**
 * @brief Сотояние U1 контроллера
 *
 * Структура, описывающая состояние контроллера U1.
 */
struct U1State
{
    /// Датчики
    QList<QVariant> sensors;

    /// Устройства
    QList<QVariant> devices;

    /// Код ошибки (0 - ошибка отсутствует. Чем больше по модулую ошибка от нуля, тем критичнее.)
    int errorCode;

    /// Состояние выполения задания адаптера (0 - адаптер совободен. 1 - адаптер занят. >= 2 - ошибка выполеннеия задания)
    unsigned int workflowState;
};

#endif // U1STATE_H

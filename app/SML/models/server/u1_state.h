#ifndef U1STATE_H
#define U1STATE_H

#include <QList>

/**
 * @brief Состояние контроллера U1
 *
 * Структура, описывающая состояние контроллера U1.
 */
struct U1State
{
    /// Датчики
    QList<QVariant> sensors;

    /// Устройства
    QList<QVariant> devices;

    /// Код ошибки
    int errorCode;

    /// Состояние выполения задания адаптера (0 - адаптер совободен. 1 - адаптер занят. >= 2 - ошибка выполеннеия задания)
    unsigned int workflowState;
};

#endif // U1STATE_H

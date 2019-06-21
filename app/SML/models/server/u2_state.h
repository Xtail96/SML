#ifndef U2_STATE_H
#define U2_STATE_H

/**
 * @brief Состояние контроллера U2
 *
 * Структура, описывающая состояние контроллера U2.
 */
struct U2State
{
    /// Код ошибки
    int errorCode;

    /// Состояние выполения задания адаптера (0 - адаптер совободен. 1 - адаптер занят. >= 2 - ошибка выполеннеия задания)
    unsigned int workflowState;
};

#endif // U2_STATE_H

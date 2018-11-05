#ifndef INTERACTOR_H
#define INTERACTOR_H

/**
 * @brief Класс Интерактор
 *
 * Базовый интерфейс для реализации в наследниках.
 */
class Interactor
{
public:

    /**
     * @brief Запускает процесс выполения интерактора
     * @warning Чисто виртуальный метод
     */
    virtual void execute() = 0;

    /**
     * @brief Виртуальный деструктор для переопределения в наследниках
     * @warning Чисто виртуальный метод
     */
    virtual ~Interactor() {}
};

#endif // INTERACTOR_H

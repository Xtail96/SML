#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include "../../../../gui/oglwidget.h"

/**
 * @brief Абстрактный класс "Команда"
 */
class Command
{
public:
    virtual ~Command() {}

    /**
     * @brief Отправляет текущую команду на станок
     */
    virtual void send() const = 0;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    virtual void draw(OGLWidget* w) const = 0;

    /**
     * @return имя текущей команды
     */
    virtual std::string getName() const = 0;

    /**
     * @return ID команды
     */
    virtual size_t getId() const = 0;

    /**
     * @return строковое представление аргументов текущей команды
     */
    virtual QString getArguments() const = 0;
};

#endif // COMMAND_H

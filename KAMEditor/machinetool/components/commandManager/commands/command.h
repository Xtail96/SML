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
    size_t getId() const { return id; }


    // скорее всего, временные методы, будет переделано при рефакторинге
    /**
     * @return цвет текущей команды в ребакторе
     */
    virtual std::string getEditorColor() const { return "#000000"; }

    /**
     * @return строковое представление аргументов текущей команды
     */
    virtual QString getArguments() const = 0;


private:
    /// ID текущей команды
    size_t id;
};

#endif // COMMAND_H

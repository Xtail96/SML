#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

#include "../../../../gui/widgets/oglwidget.h"

class OGLWidget;

/**
 * @brief Абстрактный класс "Команда"
 */
class Command
{
public:
    virtual ~Command() {}

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    virtual byte_array getDataForMachineTool() const = 0;

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
     * @return Id команды
     */
    virtual size_t getId() const = 0;

    /**
     * @return строковое представление каждого из аргументов текущей команды
     */
    virtual QStringList getArguments() const = 0;

    /**
     * @return подробное строковое представление аргументов текущей команды
     */
    virtual QString getArgumentsString() const = 0;

    /**
     * @return цвет текущей команды
     */
    virtual QColor getColor() const = 0;
};

#endif // COMMAND_H

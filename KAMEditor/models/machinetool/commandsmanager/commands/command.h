#ifndef COMMAND_H
#define COMMAND_H

#include <QString>

#include "models/structs.h"
#include "../../../../gui/oglwidget.h"

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
    virtual void draw(OGLWidget* w, Point3D sourcePoint = Point3D()) const = 0;

    virtual Point3D returnDestinationPoint(Point3D sourcePoint = Point3D()) const = 0;

    /**
     * @return имя текущей команды
     */
    virtual std::string getName() const = 0;

    /**
     * @return Id команды
     */
    virtual size_t getId() const = 0;

    /**
     * @return строковое представление аргументов текущей команды
     */
    virtual QString getArguments() const = 0;

    /**
     * @return цвет текущей команды
     */
    virtual QColor getColor() const = 0;
};

#endif // COMMAND_H

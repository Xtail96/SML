#ifndef BASEMACHINETOOL_H
#define BASEMACHINETOOL_H

#include <math.h>

struct Point3D
{
    double x;
    double y;
    double z;
};

/**
 * \brief Базовый класс "Станок"
 * \warning Является синглтоном
 *
 * Данный класс отвечает за управление станком:
 *      Перемещение по координатам
 *      /TODO Описание базового класса станок
 */
class BaseMachineTool
{
public:
    /// Возвращает экземпляр класса MachineTool
    static BaseMachineTool& Instance();

    void setMovementStep(double s) { step = s; }

    /// Возвращает текущие координаты
    Point3D getCurrentCoordinates();

    /// Возвращает координаты базы
    Point3D getBaseCoordinates();

    /// Возвращает координаты парка
    Point3D getParkCoordinates();


    void stepMove(Point3D f);

private:
    // шаг движения
    double step;

    /// Координаты базы, абсолютные
    Point3D base;

    /// Координаты парка, абсолютные
    Point3D park;

    /// Координаты точки ноль относительно базы
    Point3D zero;

    /// Текущие относительно нуля
    Point3D current;


    // конструктор и деструктор недоступны публично
    BaseMachineTool();
    ~BaseMachineTool();

    // запрет копирования
    BaseMachineTool(BaseMachineTool const&);
    BaseMachineTool& operator=(BaseMachineTool const&);
};

#endif // MACHINETOOL_H

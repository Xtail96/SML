#ifndef BASEMACHINETOOL_H
#define BASEMACHINETOOL_H

#include <math.h>

class Vector
{
public:

    double x;
    double y;
    double z;

    double a;
    double b;

    Vector() : x(), y(), z(), a(), b() {}
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
    Vector getCurrentCoordinates();

    /// Возвращает координаты базы
    Vector getBaseCoordinates();

    /// Возвращает координаты парка
    Vector getParkCoordinates();

    void setVelocity(int vel) { velocity = vel; }

    void setAcceleration(int acc) { acceleration = acc; }

    void setRotation(int j) { jog = j; }

    void stepMove(Vector f);

    void setParkCoordinates(Vector f);

private:
    // шаг движения
    double step;

    /// Координаты базы, абсолютные
    Vector base;

    /// Координаты парка, абсолютные
    Vector park;

    /// Координаты точки ноль относительно базы
    Vector zero;

    /// Текущие относительно нуля
    Vector current;

    /// Максимальное значение скорости
    int velocity;

    /// Текущее ускорение
    int acceleration;

    /// Обороты шпинделя в минуту
    int jog;


    // конструктор и деструктор недоступны публично
    BaseMachineTool();
    ~BaseMachineTool();

    // запрет копирования
    BaseMachineTool(BaseMachineTool const&);
    BaseMachineTool& operator=(BaseMachineTool const&);
};

#endif // MACHINETOOL_H

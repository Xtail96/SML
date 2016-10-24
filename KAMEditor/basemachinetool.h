#ifndef BASEMACHINETOOL_H
#define BASEMACHINETOOL_H

#include <math.h>

struct Vector3D
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
    Vector3D getCurrentCoordinates();

    /// Возвращает координаты базы
    Vector3D getBaseCoordinates();

    /// Возвращает координаты парка
    Vector3D getParkCoordinates();

    void setVelocity(int vel) { velocity = vel; }

    void setAcceleration(int acc) { acceleration = acc; }

    void setRotation(int j) { jog = j; }

    void stepMove(Vector3D f);

private:
    // шаг движения
    double step;

    /// Координаты базы, абсолютные
    Vector3D base;

    /// Координаты парка, абсолютные
    Vector3D park;

    /// Координаты точки ноль относительно базы
    Vector3D zero;

    /// Текущие относительно нуля
    Vector3D current;

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

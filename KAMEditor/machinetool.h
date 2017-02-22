#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include "vector.h"


/**
 * \brief Класс "Станок"
 * \warning Является синглтоном
 *
 * Данный класс отвечает за управление станком:
 *      Перемещение по координатам
 *      /TODO Описание класса станок
 */
class MachineTool
{
public:
    /// Возвращает экземпляр класса MachineTool
    static MachineTool& Instance();

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

    void setNewZeroCoordinates(Vector f);

    void setBaseStatus(bool value);

    bool getBaseStatus();

    void setEdgesControlEnable(bool value);

    bool getEdgesControlEnable();

private:
    // шаг движения
    double step;

    /// Текущие координаты от базы, абсолютные
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

    /// Забазирован ли станок
    bool baseStatus;

    /// Активен ли контроль габаритов
    bool edgeControlEnable;

    // конструктор и деструктор недоступны публично
    MachineTool();
    ~MachineTool();

    // запрет копирования
    MachineTool(MachineTool const&);
    MachineTool& operator=(MachineTool const&);
};

#endif // MACHINETOOL_H

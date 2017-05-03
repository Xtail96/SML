#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>
#include "vector.h"


/// Настройки KFlop
struct AxisKFlopSettings
{
    double jerk;
    double acceleration;
    double velocity;
    unsigned int channel;
    double basingVelocity;
    AxisKFlopSettings(double _jerk = 0, double _acceleration = 0, double _velocity = 0, unsigned int _channel = 0, double _basingVelocity = 0)
        : jerk(_jerk), acceleration(_acceleration), velocity(_velocity), channel(_channel), basingVelocity(_basingVelocity){}
};

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

    /// Возвращает текущие координаты
    Vector getCurrentCoordinates();

    /// Возвращает координаты базы
    Vector getBaseCoordinates();

    /// Возвращает координаты парка
    Vector getParkCoordinates();

    void setMovementStep(double s) { step = s; }

    std::string getSettingsPath();
    void setSettingsPath(std::string s);

    void setDimensions(Vector v);
    Vector getDimensions();

    void setDirections(Vector v);
    Vector getDirections();

    void setDistanceByOneStep(Vector v);
    Vector getDistanceByOneStep();

    void setStepQuantityByOneMm(Vector v);
    Vector getStepQuantityByOneMm();

    void setExternalDevices(std::map<std::string, bool> m);
    std::map<std::string, bool> getExternalDevices();

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

    void setSpindleEnable(bool value);

    bool getSpindleEnable();

    void setSpindleWarmUp(bool value);

    bool getSpindleWarmUp();

    void setAxisKFlopSettings(std::vector<AxisKFlopSettings> s);

    std::vector<AxisKFlopSettings> getAxisKFlopSettings();

    unsigned int getAxisCount();


private:
    unsigned int axisCount;

    std::vector<AxisKFlopSettings> axisKFlopSettings;

    // шаг движения
    double step;

    /// Директория для сохранения настроек
    std::string settingsPath = "settings.ini";

    /// Габариты станка
    Vector dimensions;

    /// Направления осей
    Vector directions;

    /// Расстояние, проходимое за 1 шаг
    Vector distanceByOneStep;

    /// Число шагов на 1мм
    Vector stepQuantityByOneMm;

    /// Внешние устройства
    std::map<std::string, bool> externalDevices;

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
    bool edgesControlEnable;

    /// Включен ли шпиндель
    bool spindleEnable;

    /// Проведен ли прогрев Шпинделя
    bool spindleWarmUp;

    // конструктор и деструктор недоступны публично
    MachineTool();
    ~MachineTool();

    // запрет копирования
    MachineTool(MachineTool const&);
    MachineTool& operator=(MachineTool const&);
};

#endif // MACHINETOOL_H

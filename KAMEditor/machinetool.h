#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>
#include "axis.h"
#include "structs.h"

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
    VectorDouble getCurrentCoordinates();

    /// Возвращает координаты базы
    VectorDouble getBaseCoordinates();

    /// Возвращает координаты парка
    VectorDouble getParkCoordinates();

    void setMovementStep(double s) { step = s; }

    std::string getSettingsPath();
    void setSettingsPath(std::string s);

//    void setDimensions(VectorDouble v);
//    VectorDouble getDimensions();

//    void setDirections(std::vector<bool> v);
//    std::vector<bool> getDirections();

//    void setDistanceByOneStep(VectorDouble v);
//    VectorDouble getDistanceByOneStep();

    void setExternalDevices(std::map<std::string, bool> m);
    std::map<std::string, bool> getExternalDevices();

    void setVelocity(int vel) { velocity = vel; }

    void setAcceleration(int acc) { acceleration = acc; }

    void setRotation(int j) { jog = j; }

    void stepMove(VectorDouble f);

    void setParkCoordinates(VectorDouble f);

    void setNewZeroCoordinates(VectorDouble f);

    void setBaseStatus(bool value);

    bool getBaseStatus();

    void setEdgesControlEnable(bool value);

    bool getEdgesControlEnable();

    void setSpindleEnable(bool value);

    bool getSpindleEnable();

    void setSpindleWarmUp(bool value);

    bool getSpindleWarmUp();

//    void setAxisKFlopSettings(std::vector<AxisKFlopSettings> s);

//    std::vector<AxisKFlopSettings> getAxisKFlopSettings();

    unsigned int getAxisCount();
    void setAxisCount(const unsigned int &value);


    void addMachineToolAxis(const unsigned int &count);
    std::vector<Axis> getMachineToolAxis() const;
    void setMachineToolAxis(const std::vector<Axis> &value);

    // добавить метод для настройки всех осей

private:
    unsigned int axisCount;

    // шаг движения
    double step;

    /// Директория для сохранения настроек
    std::string settingsPath = "settings.ini";

    /// Оси станка
    std::vector<Axis> machineToolAxis;

    /*/// Габариты станка
    VectorDouble dimensions;

    /// Направления осей
    std::vector<bool> directions;

    /// Расстояние, проходимое за 1 шаг
    VectorDouble distanceByOneStep;*/

    /// Внешние устройства
    std::map<std::string, bool> externalDevices;

    /// Текущие координаты от базы, абсолютные
    VectorDouble base;

    /// Координаты парка, абсолютные
    VectorDouble park;

    /// Координаты точки ноль относительно базы
    VectorDouble zero;

    /// Текущие относительно нуля
    VectorDouble current;

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

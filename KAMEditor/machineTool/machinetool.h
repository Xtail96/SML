#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "machinetool/structs.h"
#include "machinetool/settingsManager/settingsmanager.h"
#include "machinetool/components/axises/axis.h"
#include "machinetool/components/sensors/sensor.h"
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

    unsigned int getAxisCount();
    void setAxisCount(const unsigned int &value);


    void addMachineToolAxis(const unsigned int &count);
    void setupMachineToolAxises();

    std::vector<Axis>& getMachineToolAxis();
    void setMachineToolAxis(const std::vector<Axis> &value);

    std::vector<Sensor> getMachineToolSensors() const;

    void addMachineToolSensor(Sensor s);

private:
    unsigned int axisCount;

    // шаг движения
    double step;

    /// Директория для сохранения настроек
    std::string settingsPath = "settings.ini";

    /// Оси станка
    std::vector<Axis> machineToolAxis;

    //! Датчики станка
    std::vector<Sensor> machineToolSensors;

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

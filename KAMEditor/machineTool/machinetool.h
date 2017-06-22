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
#include "machinetool/components/devices/device.h"
#include "machinetool/components/movementController/movementcontroller.h"
#include "machinetool/components/pointsManager/pointsManager/pointsmanager.h"
#include "machinetool/components/commandInterpreter/commandinterpreter.h"
#include "machinetool/components/commandManager/commandsmanager.h"

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
    MachineTool();
    ~MachineTool();

    void addMachineToolAxises(const unsigned int &count);
    void setupMachineToolAxises();
private:
    /// Оси станка
    std::vector< std::shared_ptr<Axis> > axises;

    //! Датчики станка
    std::vector< std::shared_ptr<Sensor> > sensors;

    /// Внешние устройства
    std::vector< std::shared_ptr<Device> > devices;

    MovementController movementController;
    PointsManager pointsManager;
    CommandsManager commandsManager;
    CommandInterpreter commandInterpreter;
};

#endif // MACHINETOOL_H

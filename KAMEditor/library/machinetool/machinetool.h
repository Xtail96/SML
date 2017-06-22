#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "library/machinetool/structs.h"
#include "library/machinetool/settingsManager/settingsmanager.h"
#include "library/machinetool/components/axises/axis.h"
#include "library/machinetool/components/sensors/sensor.h"
#include "library/machinetool/components/devices/device.h"
#include "library/machinetool/components/movementController/movementcontroller.h"
#include "library/machinetool/components/pointsManager/pointsManager/pointsmanager.h"
#include "library/machinetool/components/commandInterpreter/commandinterpreter.h"
#include "library/machinetool/components/commandManager/commandsmanager.h"

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
    MachineTool(const unsigned int _axisCount);

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

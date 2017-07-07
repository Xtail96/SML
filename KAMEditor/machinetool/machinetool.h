#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "machinetool/structs.h"
#include "machinetool/settingsManager/settingsmanager.h"
#include "machinetool/components/sensors/sensor.h"
#include "machinetool/components/devices/device.h"
#include "machinetool/components/movementController/movementcontroller.h"
#include "machinetool/components/pointsManager/pointsManager/pointsmanager.h"
#include "machinetool/components/commandInterpreter/commandinterpreter.h"
#include "machinetool/components/commandManager/commandsmanager.h"

/**
 * \brief Класс "Станок"
 *
 * Данный класс отвечает за управление станком:
 *      Перемещение по координатам
 *      /TODO Описание класса станок
 */
class MachineTool
{
public:
    MachineTool(const unsigned int _axisesCount = 3);
    ~MachineTool();

    MovementController getMovementController() const;
    std::vector<std::shared_ptr<Sensor> > getSensors() const;
    void setSensors(const std::vector<std::shared_ptr<Sensor> > &value);

    std::vector<std::shared_ptr<Device> > getDevices() const;
    void setDevices(const std::vector<std::shared_ptr<Device> > &value);

private:
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

#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "models/structs.h"
#include "models/machinetool/settingsManager/settingsmanager.h"
#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/devicesmanager/device/device.h"
#include "models/machinetool/movementshandler/movementshandler.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"
#include "models/machinetool/commandsmanager/commandsmanager.h"

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
    MachineTool(uint16_t _vendorId, uint16_t _productId, const unsigned int _axisesCount = 3);
    ~MachineTool();

    MovementsHandler getMovementController() const;

    std::vector<std::shared_ptr<Sensor> > getSensors() const;
    void setSensors(const std::vector<std::shared_ptr<Sensor> > &value);

    std::vector<std::shared_ptr<Device> > getDevices() const;
    void setDevices(const std::vector<std::shared_ptr<Device> > &value);

    uint16_t getVendorId() const;

    uint16_t getProductId() const;

    PointsManager &getPointsManager();

private:
    uint16_t vendorId;

    uint16_t productId;

    //! Датчики станка
    std::vector< std::shared_ptr<Sensor> > sensors;

    /// Внешние устройства
    std::vector< std::shared_ptr<Device> > devices;

    MovementsHandler movementController;
    PointsManager pointsManager;
    CommandsManager commandsManager;
    CommandInterpreter commandInterpreter;
};

#endif // MACHINETOOL_H

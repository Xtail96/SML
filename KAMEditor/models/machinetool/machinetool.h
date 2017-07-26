#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "models/structs.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"
#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/devicesmanager/device/device.h"
#include "models/machinetool/movementshandler/movementshandler.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"
#include "models/machinetool/commandsmanager/commandsmanager.h"
#include "models/machinetool/sensorsmanager/sensorsmanager.h"

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
    MachineTool(uint16_t _vendorId, uint16_t _productId, std::string _name, const unsigned int _axisesCount = 3);
    ~MachineTool();

    MovementsHandler *getMovementController() const;

    uint16_t getVendorId() const;

    uint16_t getProductId() const;

    PointsManager *getPointsManager() const;

    std::string getName() const;
    void setName(const std::string &value);

    SensorsManager *getSensorsManager() const;

    StateBuffer& getBuffer();

    void checkState();

private:
    uint16_t vendorId;

    uint16_t productId;

    std::string name;

    MovementsHandler *movementController;
    PointsManager *pointsManager;
    SensorsManager *sensorsManager;
    CommandsManager *commandsManager;
    CommandInterpreter *commandInterpreter;

    StateBuffer buffer;
};

#endif // MACHINETOOL_H

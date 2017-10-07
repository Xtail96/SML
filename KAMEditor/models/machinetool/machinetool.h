#ifndef MACHINETOOL_H
#define MACHINETOOL_H

#include <math.h>
#include <map>
#include <string>
#include <vector>

#include "models/machinetool/movementshandler/movementshandler.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"
#include "models/machinetool/commandsmanager/commandsmanager.h"
#include "models/machinetool/sensorsmanager/sensorsmanager.h"
#include "models/machinetool/devicesmanager/devicesmanager.h"
#include "models/machinetool/filemanager/filemanager.h"

class FileManager;

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

    StatesBuffer& getBuffer();

    DevicesManager *getDevicesManager() const;

    CommandsManager *getCommandsManager() const;

    CommandsInterpreter *getCommandsInterpreter() const;

    unsigned int getVelocity() const;
    void setVelocity(unsigned int value);

    unsigned int getSpindelRotations() const;
    void setSpindelRotations(unsigned int value);

    FileManager *getFileManager() const;

private:
    uint16_t vendorId;

    uint16_t productId;

    std::string name;

    MovementsHandler *movementController;
    PointsManager *pointsManager;
    SensorsManager *sensorsManager;
    DevicesManager *devicesManager;
    CommandsManager *commandsManager;
    CommandsInterpreter *commandsInterpreter;
    FileManager* fileManager;

    StatesBuffer buffer;

    unsigned int velocity;
    unsigned int spindelRotations;
};

#endif // MACHINETOOL_H

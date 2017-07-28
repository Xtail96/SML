#include "machinetool.h"

MachineTool::MachineTool(uint16_t _vendorId, uint16_t _productId, std::string _name, const unsigned int _axisesCount) :
    vendorId(_vendorId), productId(_productId), name(_name),
    movementController(new MovementsHandler(_axisesCount)),
    pointsManager(new PointsManager()),
    sensorsManager(new SensorsManager()),
    devicesManager(new DevicesManager()),
    commandsManager(new CommandsManager),
    commandInterpreter(new CommandInterpreter())
{
}

MachineTool::~MachineTool()
{
    delete this->movementController;
    delete this->pointsManager;
    delete this->commandsManager;
    delete this->commandInterpreter;
    delete this->sensorsManager;
    delete this->devicesManager;
}

MovementsHandler* MachineTool::getMovementController() const
{
    return movementController;
}

uint16_t MachineTool::getVendorId() const
{
    return vendorId;
}

uint16_t MachineTool::getProductId() const
{
    return productId;
}

PointsManager *MachineTool::getPointsManager() const
{
    return pointsManager;
}

std::string MachineTool::getName() const
{
    return name;
}

void MachineTool::setName(const std::string &value)
{
    name = value;
}

SensorsManager *MachineTool::getSensorsManager() const
{
    return sensorsManager;
}

StatesBuffer &MachineTool::getBuffer()
{
    return buffer;
}

DevicesManager *MachineTool::getDevicesManager() const
{
    return devicesManager;
}

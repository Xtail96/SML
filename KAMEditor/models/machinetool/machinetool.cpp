#include "machinetool.h"

MachineTool::MachineTool(uint16_t _vendorId, uint16_t _productId, std::string _name, const unsigned int _axisesCount) :
    vendorId(_vendorId), productId(_productId), name(_name),
    movementController(new MovementsHandler(_axisesCount)),
    pointsManager(new PointsManager()),
    sensorsManager(new SensorsManager()),
    devicesManager(new DevicesManager()),
    commandsManager(new CommandsManager()),
    commandsInterpreter(new CommandsInterpreter(commandsManager)),
    smlFilesManager(new SMLFilesManager(commandsManager, pointsManager, devicesManager, movementController->getAxises().size())),
    velocity(10),
    spindelRotations(5000)
{
}

MachineTool::~MachineTool()
{
    delete this->movementController;
    delete this->pointsManager;
    delete this->commandsManager;
    delete this->commandsInterpreter;
    delete this->sensorsManager;
    delete this->devicesManager;
    delete this->smlFilesManager;
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

CommandsManager *MachineTool::getCommandsManager() const
{
    return commandsManager;
}

CommandsInterpreter *MachineTool::getCommandsInterpreter() const
{
    return commandsInterpreter;
}

unsigned int MachineTool::getVelocity() const
{
    return velocity;
}

void MachineTool::setVelocity(unsigned int value)
{
    velocity = value;
}

unsigned int MachineTool::getSpindelRotations() const
{
    return spindelRotations;
}

void MachineTool::setSpindelRotations(unsigned int value)
{
    spindelRotations = value;
}

SMLFilesManager *MachineTool::getSMLFilesManager() const
{
    return smlFilesManager;
}

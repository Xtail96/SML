#include "machinetool.h"

MachineTool::MachineTool() :
    settingsManager(new SettingsManager()),
    movementController(new MovementsHandler(settingsManager)),
    pointsManager(new PointsManager()),
    sensorsManager(new SensorsManager()),
    devicesManager(new DevicesManager()),
    //commandsManager(new CommandsManager()),
    gcodesManager(new GCodesManager()),
    //smlFilesManager(new SMLFilesManager(commandsManager, pointsManager, devicesManager, movementController->getAxises().size())),
    gcodesFilesManager(new GCodesFilesManager()),
    velocity(10),
    spindelRotations(5000)
{
    QString machineToolInformationGroupName = "MachineToolInformation";
    try
    {
            vendorId = settingsManager->get(machineToolInformationGroupName, "VendorId").toUInt();
            productId = settingsManager->get(machineToolInformationGroupName, "ProductId").toUInt();
            name = settingsManager->get(machineToolInformationGroupName, "Name").toString().toStdString();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации станка!") + QString(e.what()) + QString("; Приложение будет закрыто.")).exec();
        exit(0);
    }
}

MachineTool::~MachineTool()
{
    delete this->settingsManager;
    delete this->movementController;
    delete this->pointsManager;
    //delete this->commandsManager;
    delete this->gcodesManager;
    delete this->sensorsManager;
    delete this->devicesManager;
    //delete this->smlFilesManager;
    delete this->gcodesFilesManager;
}

void MachineTool::updateCurrentState(byte_array value)
{
    buffer.updateBuffer(value);
    sensorsManager->updateSensors(buffer);
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

/*CommandsManager *MachineTool::getCommandsManager() const
{
    return commandsManager;
}*/

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

/*SMLFilesManager *MachineTool::getSMLFilesManager() const
{
    return smlFilesManager;
}*/

GCodesManager *MachineTool::getGcodesManager() const
{
    return gcodesManager;
}

GCodesFilesManager *MachineTool::getGcodesFilesManager() const
{
    return gcodesFilesManager;
}

void MachineTool::setGcodesFilesManager(GCodesFilesManager *value)
{
    gcodesFilesManager = value;
}

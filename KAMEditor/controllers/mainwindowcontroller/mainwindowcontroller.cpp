#include "mainwindowcontroller.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent)
{
    setupMainBridge();
    setupU1Connection();
    setupTimer();
}

MainWindowController::~MainWindowController()
{
    delete timer;
    delete mainBridge;
    delete machineTool;
#ifdef Q_OS_WIN
    delete u1Manager;
#endif
}

void MainWindowController::setupMainBridge()
{
    mainBridge = new MainBridge();
}

void MainWindowController::setupU1Connection()
{
    connect(this, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(connectWithU1()));
}

void MainWindowController::setupTimer()
{
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(this, SIGNAL(u1IsConnected()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMachineToolState()));
}

QStringList MainWindowController::getSensorsNames()
{
    return mainBridge->sensorsNames(machineTool->getSensorsManager()->getSensors());
}

QStringList MainWindowController::getSensorsParametrsNames()
{
    return mainBridge->sensorsParametrsNames();
}

QList<QStringList> MainWindowController::getSensorsSettings()
{
    return mainBridge->sensorsSettings(machineTool->getSensorsManager()->getSensors());
}

QList<QColor> MainWindowController::getSensorsLeds()
{
    return mainBridge->sensorsLeds(machineTool->getSensorsManager()->getSensors());
}

QStringList MainWindowController::getDevicesNames()
{
    return mainBridge->devicesNames(machineTool->getDevicesManager()->getDevices());
}

QStringList MainWindowController::getDevicesParametrsNames()
{
    return mainBridge->devicesParametrsNames();
}

QList<QStringList> MainWindowController::getDevicesSettings()
{
    return mainBridge->devicesSettings(machineTool->getDevicesManager()->getDevices());
}

QStringList MainWindowController::getOnScreenDevicesNames()
{
    return mainBridge->onScreenDevicesNames(machineTool->getDevicesManager()->getDevices());
}

QList<bool> MainWindowController::getOnScreenDevicesStates()
{
    return mainBridge->onScreenDevicesStates(machineTool->getDevicesManager()->getDevices());
}

QStringList MainWindowController::getAxisesNames()
{
    return mainBridge->axisesNames(machineTool->getMovementController()->getAxises());
}

QStringList MainWindowController::getAxisesParametrsNames()
{
    return mainBridge->axisesParametrsNames();
}

QList<QStringList> MainWindowController::getAxisesSettings()
{
    return mainBridge->axisesSettings(machineTool->getMovementController()->getAxises());
}

unsigned int MainWindowController::getVelocity()
{
    return machineTool->getVelocity();
}

unsigned int MainWindowController::getSpindelRotations()
{
    return machineTool->getSpindelRotations();
}

QList<QStringList> MainWindowController::getPoints()
{
    return mainBridge->points(machineTool->getPointsManager());
}

QStringList MainWindowController::getPoint(unsigned int number)
{
    return mainBridge->point(machineTool->getPointsManager(), number);
}

int MainWindowController::getCommandId(QString commandName)
{
    return CommandsIds.getId(commandName.toStdString());
}

size_t MainWindowController::getCommandsCount()
{
    return machineTool->getCommandsManager()->commandsCount();
}

void MainWindowController::insertCommand(int id, QStringList arguments, size_t index)
{
    std::shared_ptr<Command> cmd = mainBridge->makeCommand(id, arguments, machineTool);
    machineTool->getCommandsManager()->insertCommand(index, cmd);
    emit commandsUpdated();
}

QList<QTreeWidgetItem *> MainWindowController::getCommands()
{
    return mainBridge->commands(machineTool->getCommandsManager());
}

QStringList MainWindowController::getCommandArguments(size_t index)
{
    std::shared_ptr<Command> cmd;
    try
    {
        cmd = machineTool->getCommandsManager()->operator [](index);
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return cmd->getArguments();
}

void MainWindowController::replaceCommand(int id, QStringList arguments, size_t index)
{
    std::shared_ptr<Command> cmd = mainBridge->makeCommand(id, arguments, machineTool);
    try
    {
        machineTool->getCommandsManager()->operator [](index) = cmd;
        emit commandsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowController::loadMachineToolSettings()
{
    SettingsManager settingsManager;
    QString machineToolInformationGroupName = "MachineToolInformation";
    try
    {
        machineTool = new MachineTool(
                    settingsManager.get(machineToolInformationGroupName, "VendorId").toUInt(),
                    settingsManager.get(machineToolInformationGroupName, "ProductId").toUInt(),
                    settingsManager.get(machineToolInformationGroupName, "Name").toString().toStdString(),
                    settingsManager.get(machineToolInformationGroupName, "AxisCount").toUInt()
                    );
        emit machineToolSettingsIsLoaded();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации", QString("Ошибка инициализации станка!") + QString(e.what()) + QString("; Приложение будет закрыто.")).exec();
        exit(0);
    }
}

void MainWindowController::connectWithU1()
{
#ifdef Q_OS_WIN
    try
    {
        u1Manager = new UsbXpressDeviceManager(machineTool->getName());
        emit u1IsConnected();
    }
    catch(std::runtime_error e)
    {
        u1Manager = nullptr;
        QMessageBox(QMessageBox::Warning, "Ошибка подключения", e.what()).exec();
        emit u1IsDisconnected();
    }
#endif
#ifdef Q_OS_UNIX
    emit u1IsDisconnected();
#endif
}

void MainWindowController::updateMachineToolState()
{

#ifdef Q_OS_WIN
    try
    {
        byte_array recieved = u1Manager->getU1()->receiveData(16);
        machineTool->getBuffer().updateBuffer(recieved);

        machineTool->getSensorsManager()->updateSensors(machineTool->getBuffer());
    }
    catch(std::runtime_error e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        timer->stop();
        emit u1IsDisconnected();
    }
#endif
#ifdef Q_OS_UNIX
    emit machineToolStateIsChanged();
#endif
}

void MainWindowController::switchDevice(QString qDeviceName)
{
    std::string deviceName = qDeviceName.toStdString();
    try
    {
        Device &device = machineTool->getDevicesManager()->findDevice(deviceName);
        byte_array data = machineTool->getDevicesManager()->getSwitchDeviceData(device, !device.getCurrentState());
#ifdef Q_OS_WIN
        if(u1Manager != nullptr)
        {
            try
            {
                u1Manager->getU1()->sendData(data);
            }
            catch(std::runtime_error e)
            {
                QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
            }
        }
        else
        {
            QMessageBox(QMessageBox::Warning, "Ошибка инициализации", "Не могу связаться со станком").exec();
        }
#endif
        device.setCurrentState(!device.getCurrentState());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowController::updateVelocity(int value)
{
    if(value > 0)
    {
        machineTool->setVelocity(value);
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Скорость не может быть отрицатльной").exec();
    }
}

void MainWindowController::updateSpindelRotations(int value)
{
    if(value > 0)
    {
        machineTool->setSpindelRotations(value);
    }
    else
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Обороты шпинделя не могут быть отрицатльными").exec();
    }
}

void MainWindowController::addPoint(QStringList coordinates)
{
    Point* p = mainBridge->makePoint(coordinates);
    machineTool->getPointsManager()->addPoint(p);
    emit pointsUpdated();
}

void MainWindowController::updatePoint(QStringList coordinates, unsigned int number)
{
    Point* p = mainBridge->makePoint(coordinates);
    try
    {
        std::shared_ptr<Point> originPoint = machineTool->getPointsManager()->operator [](number);
        unsigned int originPointDimension = originPoint->size();
        unsigned int newPointDimension = p->size();
        unsigned int rangeForUpdate = std::min(originPointDimension, newPointDimension);
        for(unsigned int i = 0; i < rangeForUpdate; i++)
        {
            originPoint->get(i) = p->get(i);
        }
        emit pointsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowController::deletePoint(unsigned int number)
{
    try
    {
        std::shared_ptr<Point> p = machineTool->getPointsManager()->operator [](number);
        machineTool->getPointsManager()->deletePoint(p);
        emit pointsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowController::deleteCommand(unsigned int number)
{
    try
    {
        machineTool->getCommandsManager()->deleteCommand(number);
        emit commandsUpdated();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindowController::inerpretCommands()
{
    machineTool->getCommandsInterpreter()->updateProgram();
}

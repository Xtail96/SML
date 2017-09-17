#include "mainwindowcontroller.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent)
{
    setupMainBridge();
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
}

void MainWindowController::updateMachineToolState()
{

#ifdef Q_OS_WIN
    try
    {
        byte_array recieved = u1Manager->getU1()->receiveData(16);
        machineTool->getBuffer().updateBuffer(recieved);

        machineTool->getSensorsManager()->updateSensors(machineTool->getBuffer());

        emit u1IsConnected();
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
    emit u1IsDisconnected();
#endif
}

void MainWindowController::setupTimer()
{
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(this, SIGNAL(machineToolSettingsIsLoaded()), timer, SLOT(start()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMachineToolState()));
}

void MainWindowController::setupMainBridge()
{
    mainBridge = new MainBridge();
    connect(this, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(connectWithU1()));
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

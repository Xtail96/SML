#include "mainwindowcontroller.h"

MainWindowController::MainWindowController(QObject *parent) : QObject(parent)
{
    mainBridge = new MainBridge();
    connect(this, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(connectWithU1()));
}

MainWindowController::~MainWindowController()
{
    delete mainBridge;
    delete machineTool;
#ifdef Q_OS_WIN
    delete u1Manager;
#endif
}

MainBridge *MainWindowController::getMainBridge() const
{
    return mainBridge;
}

void MainWindowController::setMainBridge(MainBridge *value)
{
    mainBridge = value;
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

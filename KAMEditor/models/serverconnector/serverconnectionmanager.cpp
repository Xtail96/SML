#include "serverconnectionmanager.h"

ServerConnectionManager::ServerConnectionManager()
{
    SettingsManager settingsManager;
    try
    {
        size_t axisesCount = settingsManager.get("MachineToolInformation", "AxisesCount").toUInt();
        currentState = new MachineToolState(axisesCount, 16);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка инициализации подключения к серверу", QString("Ошибка инициализации подключения к серверу!") + QString(e.what())).exec();
    }
}

ServerConnectionManager::~ServerConnectionManager()
{
    delete currentState;
}

byte_array ServerConnectionManager::getSensorsState()
{
    return currentState->sensorsState.getSensorsState();
}

void ServerConnectionManager::setSensorsState(byte_array value)
{
    currentState->sensorsState.setSensorsState(value);
    emit machineToolStateIsChanged();
}

std::map<std::string, double> ServerConnectionManager::getMachineToolCoordinates()
{
    return currentState->axisesState.getAxisesCoordinates();
}

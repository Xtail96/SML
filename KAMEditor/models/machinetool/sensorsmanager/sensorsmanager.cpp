#include "sensorsmanager.h"
std::vector<std::shared_ptr<Sensor> >& SensorsManager::getSensors()
{
    return sensors;
}

void SensorsManager::updateSensors(const StatesBuffer buffer)
{
    for(auto sensor : sensors)
    {
        bool isVoltage = buffer.getSensorState(sensor->getBoardName(), sensor->getPortNumber(), sensor->getInputNumber());
        sensor->setCurrentState(isVoltage);
    }
}

SensorsManager::SensorsManager()
{
    initilize();
}

SensorsManager::SensorsManager(const SensorsManager &object) :
    sensors(object.sensors)
{

}

void SensorsManager::initilize()
{
    SettingsManager settingsManager;
    try
    {
        unsigned int sensorsCount = QVariant(settingsManager.get("MachineToolInformation", "SensorsCount")).toUInt();

        std::vector<QString> sensorsCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorString = QString("Sensor") + QString::number(i);
            sensorsCodes.push_back(sensorString);
        }

        for(auto code : sensorsCodes)
        {
            Sensor* sensor = new Sensor(code);
            sensors.push_back(std::shared_ptr<Sensor>(sensor));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка файла настроек", e.what()).exec();
    }
}

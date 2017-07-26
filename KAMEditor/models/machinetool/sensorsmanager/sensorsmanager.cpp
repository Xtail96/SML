#include "sensorsmanager.h"
std::vector<std::shared_ptr<Sensor> >& SensorsManager::getSensors()
{
    return sensors;
}

SensorsManager::SensorsManager()
{
    initilize();
}

void SensorsManager::initilize()
{
    SettingsManager settingsManager;
    try
    {
        unsigned int sensorsCount = QVariant(settingsManager.get("Sensors", "count")).toUInt();

        std::vector<std::string> sensorsNames;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            std::string sensorNumberString = std::to_string(i);
            QVariant tmp = settingsManager.get("Sensors", QString::fromStdString(sensorNumberString));
            sensorsNames.push_back(tmp.toString().toStdString());
        }

        for(unsigned int i = 0; i < sensorsNames.size(); i++)
        {
            Sensor* tmp = new Sensor(sensorsNames[i]);
            tmp->setup(settingsManager);
            sensors.push_back(std::shared_ptr<Sensor>(tmp));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка файла настроек", e.what()).exec();
    }
}

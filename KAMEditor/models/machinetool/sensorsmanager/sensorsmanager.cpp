#include "sensorsmanager.h"

std::vector<std::shared_ptr<Sensor> > SensorsManager::getSensors() const
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

        QStringList sensorsNames;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString qSensorNumberString = QString::fromStdString(std::to_string(i));
            QVariant tmp = settingsManager.get("Sensors", qSensorNumberString);
            sensorsNames.push_back(tmp.toString());
        }

        for(int i = 0; i < sensorsNames.size(); i++)
        {
            QString currentSensorName = sensorsNames[i];

            unsigned int portNumber = QVariant(settingsManager.get(currentSensorName, "portNumber")).toUInt();
            unsigned int inputNumber = QVariant(settingsManager.get(currentSensorName, "inputNumber")).toUInt();
            bool defaultState = QVariant(settingsManager.get(currentSensorName, "defaultState")).toBool();
            Sensor* tmp = new Sensor(currentSensorName.toStdString(), portNumber, inputNumber, defaultState);
            sensors.push_back(std::shared_ptr<Sensor>(tmp));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка файла настроек", e.what()).exec();
    }
}

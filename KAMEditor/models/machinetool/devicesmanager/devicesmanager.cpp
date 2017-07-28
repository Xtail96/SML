#include "devicesmanager.h"

std::vector<std::shared_ptr<Device> > &DevicesManager::getDevices()
{
    return devices;
}

void DevicesManager::updateDevices(const std::vector<std::shared_ptr<Device> > &value)
{
    devices = value;
}

void DevicesManager::initialize()
{
    SettingsManager settingsManager;
    try
    {
        unsigned int devicesCount = QVariant(settingsManager.get("Devices", "count")).toUInt();

        std::vector<std::string> devicesNames;
        for(unsigned int i = 0; i < devicesCount; i++)
        {
            std::string deviceNumberString = std::to_string(i);
            QVariant tmp = settingsManager.get("Devices", QString::fromStdString(deviceNumberString));
            devicesNames.push_back(tmp.toString().toStdString());
        }

        for(unsigned int i = 0; i < devicesNames.size(); i++)
        {
            Device* tmp = new Device(devicesNames[i]);
            tmp->setup(settingsManager);
            devices.push_back(std::shared_ptr<Device>(tmp));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка файла настроек", e.what()).exec();
    }
}

DevicesManager::DevicesManager()
{
    initialize();
}

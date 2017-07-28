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

DevicesBuffer DevicesManager::getDevicesBuffer() const
{
    return devicesBuffer;
}

DevicesManager::DevicesManager()
{
    initialize();
}

byte_array DevicesManager::getSwitchDevicePackege(std::string deviceName, bool turnOn, byte firstAgrument, byte secondArgument)
{
//    Device device = findDevice(deviceName);
//    byte switchKey = getSwitchKey(device->getBoardName(), device->getPortNumber(), device->getOutputNumber());
//    switchKey = devicesBuffer.createPackege(switchKey, turnOn);
//    byte_array data =
//    {
//        switchKey,
//        firstAgrument,
//        secondArgument
//    };
//    return data;
}

Device &DevicesManager::findDevice(std::string deviceName)
{
    for(auto it : devices)
    {
        if(it->getName() == deviceName)
        {
            return *it;
        }
    }
    std::string errorString = "device not found";
    throw std::invalid_argument(errorString);
}

byte DevicesManager::getSwitchKey(std::string boardName, unsigned int portNumber, unsigned int outputNumber)
{
//    byte switchKey = 0xff;
//    if(boardName == "u1")
//    {
//        switch(portNumber){
//        case 0:
//            switch (outputNumber) {
//            case 3:
//                switchKey = 0xfb;
//                break;
//            default:
//                break;
//            }
//            break;
//        case 1:
//            switch (outputNumber) {
//            case 3:
//                switchKey = 0xfe;
//                break;
//            case 5:
//                switchKey = 0x1f;
//                break;
//            case 7:
//                switchKey = 0xfd;
//                break;
//            default:
//                break;
//            }
//            break;
//        case 2:
//            switch (outputNumber) {
//            case 0:
//                switchKey = 0xf7;
//                break;
//            default:
//                break;
//            }
//        default:
//            break;
//        }
//    }
//    return switchKey;
}

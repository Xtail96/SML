#include "devicesmanager.h"

DevicesManager::DevicesManager(SettingsManager *sm)
{
    if(sm == nullptr)
    {
        qDebug() << "new SettingsManager instance in devicesManager";
        sm = new SettingsManager();
        initialize(sm);
        delete sm;
    }
    else
    {
        initialize(sm);
    }
}

DevicesManager::DevicesManager(const DevicesManager &object) :
    devices(object.devices),
    devicesBuffer(object.devicesBuffer)
{

}

void DevicesManager::initialize(SettingsManager *sm)
{
    try
    {
        unsigned int devicesCount = QVariant(sm->get("MachineToolInformation", "DevicesCount")).toUInt();

        std::vector<QString> devicesCodes;
        for(unsigned int i = 0; i < devicesCount; i++)
        {
            QString deviceString = QString("Device") + QString::number(i);
            devicesCodes.push_back(deviceString);
        }

        for(auto code : devicesCodes)
        {
            Device* device = new Device(code, sm);
            devices.push_back(std::shared_ptr<Device>(device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
    }
}

Device &DevicesManager::findDevice(QString deviceName)
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

byte_array DevicesManager::getSwitchDeviceData(const Device &device, bool onOff, byte firstAgrument, byte secondArgument)
{
    //byte deviceMask = getDeviceMask(device.getBoardName(), device.getPortNumber(), device.getOutputNumber());
    byte deviceMask = device.getMask();
    byte devicesMask = devicesBuffer.getDevicesMask(deviceMask, onOff);
    byte_array data =
    {
        SET_DEVICES,
        devicesMask,
        firstAgrument,
        secondArgument
    };
    return data;
}

byte DevicesManager::getDeviceMask(QString boardName, unsigned int portNumber, unsigned int outputNumber)
{
    byte deviceMask = 0xff;
    if(boardName == "u1")
    {
        switch(portNumber){
        case 0:
            switch (outputNumber) {
            case 3:
                deviceMask = 0xfb;
                break;
            default:
                break;
            }
            break;
        case 1:
            switch (outputNumber) {
            case 3:
                deviceMask = 0xfe;
                break;
            case 5:
                deviceMask = 0xef;
                break;
            case 7:
                deviceMask = 0xfd;
                break;
            default:
                break;
            }
            break;
        case 2:
            switch (outputNumber) {
            case 0:
                deviceMask = 0xf7;
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
    return deviceMask;
}

std::vector<std::shared_ptr<Device> > &DevicesManager::getDevices()
{
    return devices;
}

DevicesBuffer DevicesManager::getDevicesBuffer() const
{
    return devicesBuffer;
}

void DevicesManager::updateDevices(const std::vector<std::shared_ptr<Device> > &value)
{
    devices = value;
}

void DevicesManager::updateDevices(const byte_array devicesState)
{
    devicesBuffer.setDevicesState(devicesState[0]);
    for(auto device : devices)
    {
        bool isEnable = devicesBuffer.getDeviceState(device->getMask());
        device->setCurrentState(isEnable);
    }
}

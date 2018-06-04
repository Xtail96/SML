#include "devicesmanager.h"

DevicesManager::DevicesManager(const SettingsManager &sm)
{
    initialize(sm);
}

DevicesManager::DevicesManager(const DevicesManager &object) :
    m_devices(object.m_devices),
    m_devicesBuffer(object.m_devicesBuffer)
{

}

void DevicesManager::initialize(const SettingsManager &sm)
{
    try
    {
        unsigned int devicesCount = QVariant(sm.get("MachineToolInformation", "DevicesCount")).toUInt();

        std::vector<QString> devicesCodes;
        for(unsigned int i = 0; i < devicesCount; i++)
        {
            QString deviceString = QString("Device") + QString::number(i);
            devicesCodes.push_back(deviceString);
        }

        for(auto code : devicesCodes)
        {
            Device* device = new Device(code, sm);
            m_devices.push_back(QSharedPointer<Device>(device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
    }
}

Device &DevicesManager::findDevice(QString deviceName)
{
    for(auto it : m_devices)
    {
        if(it->getName() == deviceName)
        {
            return *it;
        }
    }
    std::string errorString = "device not found";
    throw std::invalid_argument(errorString);
}

QStringList DevicesManager::devicesNames()
{
    QStringList names;
    for(auto device : m_devices)
    {
        names.push_back(device->getName());
    }
    return names;
}

QStringList DevicesManager::devicesParametrsNames()
{
    QStringList parametrsNames =
    {
        "Имя платы",
        "Номер порта",
        "Номер выхода",
        "Активное состояние",
        "Маска",
    };
    return parametrsNames;
}

QList<QStringList> DevicesManager::devicesSettings()
{
    QList<QStringList> devicesSettings;
    for(auto device : m_devices)
    {
        QStringList deviceSettings =
        {
            device->getBoardName(),
            QString::number(device->getPortNumber()),
            QString::number(device->getOutputNumber()),
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }
    return devicesSettings;
}

QStringList DevicesManager::onScreenDevicesNames()
{
    QStringList names;
    for(auto device : m_devices)
    {
        if(device->getNeedToDisplay())
        {
            names.push_back(device->getName());
        }
    }
    return names;
}

QList<bool> DevicesManager::onScreenDevicesStates()
{
    QList<bool> devicesStates;
    for(auto device : m_devices)
    {
        if(device->getNeedToDisplay())
        {
            devicesStates.push_back(device->isEnable());
        }
    }
    return devicesStates;
}

byte_array DevicesManager::switchDeviceData(const Device &device, bool onOff, byte firstAgrument, byte secondArgument)
{
    //byte deviceMask = getDeviceMask(device.getBoardName(), device.getPortNumber(), device.getOutputNumber());
    byte deviceMask = device.getMask();
    byte devicesMask = m_devicesBuffer.getDevicesMask(deviceMask, onOff);
    byte_array data =
    {
        SET_DEVICES,
        devicesMask,
        firstAgrument,
        secondArgument
    };
    return data;
}

byte DevicesManager::deviceMask(QString boardName, unsigned int portNumber, unsigned int outputNumber)
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

QList<QSharedPointer<Device> > &DevicesManager::devices()
{
    return m_devices;
}

DevicesBuffer DevicesManager::devicesBuffer() const
{
    return m_devicesBuffer;
}

void DevicesManager::updateDevices(const QList< QSharedPointer<Device> > &value)
{
    m_devices = value;
}

void DevicesManager::updateDevices(const byte_array devicesState)
{
    m_devicesBuffer.setDevicesState(devicesState[0]);
    for(auto device : m_devices)
    {
        bool enable = m_devicesBuffer.getDeviceState(device->getMask());
        bool deviceState;
        if(enable)
        {
            deviceState = device->getActiveState();
        }
        else
        {
            deviceState = !(device->getActiveState());
        }
        device->setCurrentState(deviceState);
    }
}

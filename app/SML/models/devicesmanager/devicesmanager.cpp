#include "devicesmanager.h"

DevicesManager::DevicesManager(const SettingsManager &sm)
{
    initialize(sm);
}

DevicesManager::DevicesManager(const DevicesManager &object) :
    m_spindels(object.m_spindels),
    m_supportDevices(object.m_supportDevices),
    m_devicesBuffer(object.m_devicesBuffer)
{

}

void DevicesManager::initialize(const SettingsManager &sm)
{
    try
    {
        unsigned int spindelsCount = QVariant(sm.get("MachineToolInformation", "SpindelsCount")).toUInt();
        unsigned int supportDevicesCount = QVariant(sm.get("MachineToolInformation", "SupportDevicesCount")).toUInt();

        for(unsigned int i = 0; i < spindelsCount; i++)
        {
            QString spindelCode = QString("Spindel") + QString::number(i);
            Device* spindel = new Spindel(spindelCode, sm);
            m_spindels.push_back(QSharedPointer<Device> (spindel));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString supportDeviceCode = QString("SupportDevice") + QString::number(i);
            Device* device = new SupportDevice(supportDeviceCode, sm);
            m_supportDevices.push_back(QSharedPointer<Device> (device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
    }
}

Device &DevicesManager::findDevice(QString deviceName)
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;

    for(auto device : allDevices)
    {
        if(device->getLabel() == deviceName)
        {
            return *device;
        }
    }
    std::string errorString = "device not found";
    throw std::invalid_argument(errorString);
}

Device &DevicesManager::findDevice(unsigned int index)
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;

    for(auto device : allDevices)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }
    std::string errorString = "device not found";
    throw std::invalid_argument(errorString);
}

QStringList DevicesManager::getAllDevicesNames()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QStringList names;
    for(auto device : allDevices)
    {
        names.push_back(device->getLabel());
    }
    return names;
}

QStringList DevicesManager::getDevicesParametrsNames()
{
    QStringList parametrsNames =
    {
        "Активное состояние",
        "Маска",
    };
    return parametrsNames;
}

QList<QStringList> DevicesManager::getDevicesSettings()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QList<QStringList> devicesSettings;
    for(auto device : allDevices)
    {
        QStringList deviceSettings =
        {
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }
    return devicesSettings;
}

QStringList DevicesManager::onScreenDevicesNames()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QStringList names;
    for(auto device : allDevices)
    {
        names.push_back(device->getLabel());
    }
    return names;
}

QList<bool> DevicesManager::onScreenDevicesStates()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QList<bool> devicesStates;
    for(auto device : allDevices)
    {
        devicesStates.push_back(device->isEnable());
    }
    return devicesStates;
}

QStringList DevicesManager::getDeviceSwitchParams(size_t index, bool onOff)
{
    QStringList deviceData;
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;

    deviceData.push_back(QString::number(index));
    if(onOff)
    {
        deviceData.push_back("1");
    }
    else
    {
        deviceData.push_back("0");
    }

    for(auto device : allDevices)
    {
        if(device->getIndex().toUInt() == index)
        {
            deviceData += device->getParams();
            break;
        }
    }
    return deviceData;
}

QList<QSharedPointer<Device> > &DevicesManager::devices()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    return allDevices;
}

void DevicesManager::updateDevices(const byte_array devicesState)
{
    for(size_t i = 0; i < devicesState.size(); i++)
    {
        try
        {
            Device& device = findDevice(i);
            if(devicesState[i] == 0x01)
            {
                device.updateCurrentState(true);
            }
            else
            {
                if(devicesState[i] == 0x00)
                {
                    device.updateCurrentState(false);
                }
            }
        }
        catch(std::invalid_argument e)
        {
            qDebug() << e.what() << i;
        }
    }

    /*m_devicesBuffer.setDevicesState(devicesState[0]);
    for(auto device : allDevices)
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
        device->updateCurrentState(deviceState);
    }*/
}

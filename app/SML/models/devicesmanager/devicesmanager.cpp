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
            Spindel* spindel = new Spindel(spindelCode, sm);
            m_spindels.push_back(QSharedPointer<Spindel> (spindel));
        }

        for(unsigned int i = 0; i < supportDevicesCount; i++)
        {
            QString supportDeviceCode = QString("SupportDevice") + QString::number(i);
            SupportDevice* device = new SupportDevice(supportDeviceCode, sm);
            m_supportDevices.push_back(QSharedPointer<SupportDevice> (device));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера устройств", e.what()).exec();
    }
}

Device &DevicesManager::findDevice(size_t index)
{
    for(auto device : m_spindels)
    {
        if(device->getIndex().toUInt() == index)
        {
            return *device;
        }
    }

    for(auto device : m_supportDevices)
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
    QStringList names;
    for(auto device : m_spindels)
    {
        names.push_back(device->getLabel());
    }
    for(auto device : m_supportDevices)
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
    QList<QStringList> devicesSettings;
    for(auto device : m_spindels)
    {
        QStringList deviceSettings =
        {
            QString::number(device->getActiveState()),
            QString::number(device->getMask(), 2)
        };
        devicesSettings.push_back(deviceSettings);
    }

    for(auto device : m_supportDevices)
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
    QStringList names;
    for(auto device : m_spindels)
    {
        names.push_back(device->getLabel());
    }
    for(auto device : m_supportDevices)
    {
        names.push_back(device->getLabel());
    }
    return names;
}

QList<bool> DevicesManager::onScreenDevicesStates()
{
    QList<bool> devicesStates;
    for(auto device : m_spindels)
    {
        devicesStates.push_back(device->isEnable());
    }
    for(auto device : m_supportDevices)
    {
        devicesStates.push_back(device->isEnable());
    }
    return devicesStates;
}

QList<Spindel> DevicesManager::getSpindels()
{
    QList<Spindel> spindels;
    for(auto spindel : m_spindels)
    {
        spindels.push_back(*(spindel.data()));
    }
    return spindels;
}

Spindel &DevicesManager::findSpindel(QString name)
{
    for(auto spindel : m_spindels)
    {
        if(spindel->getName() == name)
        {
            return *(spindel.data());
        }
    }

    std::string errorString = "spindel " + name.toStdString() + " not found";
    throw std::invalid_argument(errorString);
}

QStringList DevicesManager::getSwitchSpindelParams(QString name)
{
    QStringList params;
    try
    {
        Spindel &spindel = findSpindel(name);
        params = spindel.getParams();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
    return params;
}

void DevicesManager::setSpindelRotations(QString name, size_t rotations)
{
    try
    {
        Spindel &spindel = findSpindel(name);
        spindel.setCurrentRotations(rotations);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

QStringList DevicesManager::getDeviceSwitchParams(size_t index, bool onOff)
{
    QStringList deviceData;

    deviceData.push_back(QString::number(index));
    if(onOff)
    {
        deviceData.push_back("1");
    }
    else
    {
        deviceData.push_back("0");
    }

    for(auto device : m_spindels)
    {
        if(device->getIndex().toUInt() == index)
        {
            deviceData += device->getParams();
            break;
        }
    }
    return deviceData;
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

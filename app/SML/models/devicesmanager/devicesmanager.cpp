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

    for(auto it : allDevices)
    {
        if(it->getName() == deviceName)
        {
            return *it;
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
        names.push_back(device->getName());
    }
    return names;
}

QStringList DevicesManager::getDevicesParametrsNames()
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

QList<QStringList> DevicesManager::getDevicesSettings()
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QList<QStringList> devicesSettings;
    for(auto device : allDevices)
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
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QStringList names;
    for(auto device : allDevices)
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
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    QList<bool> devicesStates;
    for(auto device : allDevices)
    {
        if(device->getNeedToDisplay())
        {
            devicesStates.push_back(device->isEnable());
        }
    }
    return devicesStates;
}

byte DevicesManager::getDeviceSwitchMask(const Device &device, bool onOff)
{
    byte deviceMask = device.getMask();
    return m_devicesBuffer.getDevicesMask(deviceMask, onOff);
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
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    return allDevices;
}

void DevicesManager::updateDevices(const byte_array devicesState)
{
    QList< QSharedPointer<Device> > allDevices = m_spindels + m_supportDevices;
    m_devicesBuffer.setDevicesState(devicesState[0]);
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
        device->setCurrentState(deviceState);
    }
}

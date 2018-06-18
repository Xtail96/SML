#include "sensorsmanager.h"

SensorsManager::SensorsManager(const SettingsManager &sm, QObject *parent) :
    QObject(parent)
{
    initialize(sm);
}

SensorsManager::SensorsManager(const SensorsManager &object) :
    m_sensors(object.m_sensors)
{
}

void SensorsManager::initialize(const SettingsManager &sm)
{
    try
    {
        unsigned int sensorsCount = QVariant(sm.get("MachineToolInformation", "SensorsCount")).toUInt();

        std::vector<QString> sensorsCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorString = QString("Sensor") + QString::number(i);
            sensorsCodes.push_back(sensorString);
        }

        for(auto code : sensorsCodes)
        {
            Sensor* sensor = new Sensor(code, sm, this);
            m_sensors.push_back(QSharedPointer<Sensor>(sensor));
        }

        size_t bufferSize = QVariant(sm.get("MachineToolInformation", "SensorsBufferSize")).toUInt();
        m_sensorsBuffer.resetBuffer(bufferSize);
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера датчиков", e.what()).exec();
    }
}

void SensorsManager::updateSensors(const byte_array sensorsState)
{
    m_sensorsBuffer.updateBuffer(sensorsState);
    for(auto sensor : m_sensors)
    {
        bool isVoltage = m_sensorsBuffer.getInputState(sensor->getBoardName(), sensor->getPortNumber(), sensor->getInputNumber());
        sensor->update(isVoltage);
    }
}

bool SensorsManager::sensorStateByName(QString sensorName)
{
    bool enable = false;
    for(auto sensor : m_sensors)
    {
        if(sensor->getName() == sensorName)
        {
            enable = sensor->isEnable();
            break;
        }
    }
    return enable;
}

QList<QColor> SensorsManager::sensorsLeds()
{
    QList<QColor> sensorsLeds;
    for(auto sensor : m_sensors)
    {
        QColor sensorLed(SmlColors::white());
        if(sensor->isEnable())
        {
            sensorLed = sensor->getColor();
        }
        sensorsLeds.push_back(sensorLed);
    }
    return sensorsLeds;
}

Sensor *SensorsManager::findSensor(QString name)
{
    Sensor* currentSensor = nullptr;
    for(auto sensor : m_sensors)
    {
        if(sensor->getName() == name)
        {
            currentSensor = sensor.data();
            break;
        }
    }
    return currentSensor;
}

QString SensorsManager::sensorSettings(QString name)
{
    return findSensor(name)->getSettings();
}

QStringList SensorsManager::sensorsSettings()
{
    QStringList settings;
    for(auto sensor : m_sensors)
    {
        settings.push_back(sensor->getSettings());
    }
    return settings;
}

QStringList SensorsManager::sensorsNames()
{
    QStringList names;
    for(auto sensor : m_sensors)
    {
        names.push_back(sensor->getName());
    }
    return names;
}

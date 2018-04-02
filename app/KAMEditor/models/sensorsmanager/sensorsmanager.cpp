#include "sensorsmanager.h"

SensorsManager::SensorsManager(SettingsManager *sm)
{
    if(sm == nullptr)
    {
        qDebug() << "new SettingsManager instance in sensorsManager";
        sm = new SettingsManager();
        initilize(sm);
        delete sm;
    }
    else
    {
        initilize(sm);
    }
}

SensorsManager::SensorsManager(const SensorsManager &object) :
    m_sensors(object.m_sensors)
{
}

void SensorsManager::initilize(SettingsManager *sm)
{
    try
    {
        unsigned int sensorsCount = QVariant(sm->get("MachineToolInformation", "SensorsCount")).toUInt();

        std::vector<QString> sensorsCodes;
        for(unsigned int i = 0; i < sensorsCount; i++)
        {
            QString sensorString = QString("Sensor") + QString::number(i);
            sensorsCodes.push_back(sensorString);
        }

        for(auto code : sensorsCodes)
        {
            Sensor* sensor = new Sensor(code, sm);
            m_sensors.push_back(std::shared_ptr<Sensor>(sensor));
        }
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки менеджера датчиков", e.what()).exec();
    }
}

std::vector<std::shared_ptr<Sensor> >& SensorsManager::sensors()
{
    return m_sensors;
}

void SensorsManager::updateSensors(const SensorsBuffer buffer)
{
    for(auto sensor : m_sensors)
    {
        bool isVoltage = buffer.getInputState(sensor->getBoardName(), sensor->getPortNumber(), sensor->getInputNumber());
        sensor->setCurrentState(isVoltage);
    }
}

void SensorsManager::updateSensors(const byte_array sensorsState)
{
    m_buffer.updateBuffer(sensorsState);
    for(auto sensor : m_sensors)
    {
        bool isVoltage = m_buffer.getInputState(sensor->getBoardName(), sensor->getPortNumber(), sensor->getInputNumber());
        sensor->setCurrentState(isVoltage);
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

QStringList SensorsManager::sensorsLabels()
{
    QStringList labels;
    for(auto sensor : m_sensors)
    {
        labels.push_back(sensor->getLabel());
    }
    return labels;
}

QStringList SensorsManager::sensorParametrLabels()
{
    QStringList parametrsLabels =
    {
        "Имя датчика",
        "Имя платы",
        "Номер порта",
        "Номер входа",
        "Активное состояние",
    };
    return parametrsLabels;
}

QList<QStringList> SensorsManager::sensorsSettings()
{
    QList<QStringList> sensorsSettings;
    for(auto sensor : m_sensors)
    {
        QStringList sensorSettings =
        {
            sensor->getName(),
            sensor->getBoardName(),
            QString::number(sensor->getPortNumber()),
            QString::number(sensor->getInputNumber()),
            QString::number(sensor->getActiveState())
        };
        sensorsSettings.push_back(sensorSettings);
    }
    return sensorsSettings;
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

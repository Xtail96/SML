#include "sensors_repository.h"

SensorsRepository::SensorsRepository():
    IRepository(),
    m_sensors()
{

}

SensorsRepository::~SensorsRepository()
{

}

bool SensorsRepository::exists(QString id)
{
    for(auto sensor : m_sensors)
    {
        if(sensor.id() == id)
            return true;
    }
    return false;
}

Sensor &SensorsRepository::get(QString id)
{
    for(auto& sensor : m_sensors)
    {
        if(sensor.id() == id)
            return sensor;
    }

    throw std::invalid_argument("unknown sensor " + id.toStdString());
}

QList<Sensor> SensorsRepository::getAll()
{
    QList<Sensor> sensors = m_sensors;
    std::sort(sensors.begin(), sensors.end());
    return sensors;
}

void SensorsRepository::add(Sensor value)
{
    if(this->exists(value.id()))
    {
        qWarning() << "Sensor" << value.id() << "is already exists. Ignored.";
        return;
    }
    m_sensors.append(value);
}

void SensorsRepository::remove(QString id)
{
    m_sensors.removeAll(this->get(id));
}

void SensorsRepository::clear()
{
    m_sensors.clear();
}

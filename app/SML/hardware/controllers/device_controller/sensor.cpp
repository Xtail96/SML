#include "sensor.h"

Sensor::Sensor(QString id,
               bool activeState,
               bool currentState,
               QString label,
               QColor ledColor) :
    m_id(id),
    m_label(label),
    m_activeState(activeState),
    m_currentState(currentState),
    m_ledColor(ledColor)
{
}

bool Sensor::operator<(const Sensor &sensor) const
{
    return this->m_id < sensor.id();
}

bool Sensor::operator>(const Sensor &sensor) const
{
    return this->m_id > sensor.id();
}

bool Sensor::operator<=(const Sensor &sensor) const
{
    return this->m_id <= sensor.id();
}

bool Sensor::operator>=(const Sensor &sensor) const
{
    return this->m_id >= sensor.id();
}

bool Sensor::operator==(const Sensor &sensor) const
{
    return this->m_id == sensor.id();
}

bool Sensor::currentState() const
{
    return m_currentState;
}

QString Sensor::id() const
{
    return m_id;
}

bool Sensor::activeState() const
{
    return m_activeState;
}

QColor Sensor::ledColor() const
{
    return m_ledColor;
}

bool Sensor::isEnabled()
{
    return (m_activeState == m_currentState);
}

QString Sensor::label() const
{
    return m_label;
}

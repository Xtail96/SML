#include "sensor.h"

Sensor::Sensor(QString id,
               bool enabled,
               QString label,
               QColor ledColor) :
    m_id(id),
    m_label(label),
    m_enabled(enabled),
    m_ledColor(ledColor)
{
    if(m_label == "")
        m_label = m_id;
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

QString Sensor::id() const
{
    return m_id;
}

QColor Sensor::ledColor() const
{
    return m_ledColor;
}

QString Sensor::label() const
{
    return m_label;
}

bool Sensor::enabled() const
{
    return m_enabled;
}

void Sensor::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

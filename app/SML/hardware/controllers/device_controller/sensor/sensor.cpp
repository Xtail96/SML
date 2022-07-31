#include "sensor.h"

Sensor::Sensor(QString uid,
               QString label,
               bool inputActiveState,
               QColor color,
               QObject *parent) :
    QObject(parent),
    m_uid(uid),
    m_label(label),
    m_activeState(inputActiveState),
    m_currentState(!m_activeState),
    m_ledColorActiveState(color)
{
}

bool Sensor::operator<(const Sensor &sensor)
{
    return this->m_uid < sensor.uid();
}

bool Sensor::operator==(const Sensor &sensor)
{
    return this->m_uid == sensor.uid();
}

bool Sensor::currentState() const
{
    return m_currentState;
}

void Sensor::setCurrentState(bool value)
{
    if(m_currentState != value)
    {
        m_currentState = value;
        emit this->stateChanged();
    }
}

QString Sensor::uid() const
{
    return m_uid;
}

bool Sensor::activeState() const
{
    return m_activeState;
}

QColor Sensor::ledColorActiveState() const
{
    return m_ledColorActiveState;
}

bool Sensor::isEnable()
{
    return (m_activeState == m_currentState);
}

QString Sensor::label() const
{
    return m_label;
}

QString Sensor::settings()
{
    QString sensorSettings = QStringLiteral("Label:") + m_label + QStringLiteral(";") +
            QStringLiteral("Uid:") + m_uid + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(m_activeState) + QStringLiteral(";") +
            QStringLiteral("LedColor:") + m_ledColorActiveState.name();
    return sensorSettings;
}

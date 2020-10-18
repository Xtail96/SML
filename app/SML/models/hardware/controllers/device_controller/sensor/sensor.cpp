#include "sensor.h"

Sensor::Sensor(QString uid,
               QString label,
               size_t portNumber,
               size_t inputNumber,
               QString boardName,
               bool inputActiveState,
               QColor color,
               QObject *parent) :
    QObject(parent),
    m_uid(uid),
    m_label(label),
    m_boardName(boardName),
    m_portNumber(portNumber),
    m_inputNumber(inputNumber),
    m_activeState(inputActiveState),
    m_inputState(!m_activeState),
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

bool Sensor::inputState() const
{
    return m_inputState;
}

void Sensor::setInputState(bool value)
{
    if(m_inputState != value)
    {
        m_inputState = value;
        emit this->stateChanged();
    }
}

size_t Sensor::portNumber() const
{
    return m_portNumber;
}

size_t Sensor::inputNumber() const
{
    return m_inputNumber;
}

QString Sensor::uid() const
{
    return m_uid;
}

QString Sensor::boardName() const
{
    return m_boardName;
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
    return (m_activeState == m_inputState);
}

QString Sensor::label() const
{
    return m_label;
}

QString Sensor::settings()
{
    QString sensorSettings = QStringLiteral("Label:") + m_label + QStringLiteral(";") +
            QStringLiteral("Uid:") + m_uid + QStringLiteral(";") +
            QStringLiteral("Board:") + m_boardName + QStringLiteral(";") +
            QStringLiteral("Port:") + QString::number(m_portNumber) + QStringLiteral(";") +
            QStringLiteral("Input:") + QString::number(m_inputNumber) + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(m_activeState) + QStringLiteral(";") +
            QStringLiteral("LedColor:") + m_ledColorActiveState.name();
    return sensorSettings;
}

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
    m_inputActiveState(inputActiveState),
    m_inputCurrentState(!m_inputActiveState),
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

void Sensor::updateInputState(bool state)
{
    this->setInputCurrentState(state);
}

bool Sensor::inputCurrentState() const
{
    return m_inputCurrentState;
}

void Sensor::setInputCurrentState(bool value)
{
    if(m_inputCurrentState != value)
    {
        m_inputCurrentState = value;
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

bool Sensor::inputActiveState() const
{
    return m_inputActiveState;
}

QColor Sensor::ledColorActiveState() const
{
    return m_ledColorActiveState;
}

bool Sensor::isEnable()
{
    return (m_inputActiveState == m_inputCurrentState);
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
            QStringLiteral("ActiveState:") + QString::number(m_inputActiveState) + QStringLiteral(";") +
            QStringLiteral("LedColor:") + m_ledColorActiveState.name();
    return sensorSettings;
}

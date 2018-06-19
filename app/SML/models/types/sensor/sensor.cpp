#include "sensor.h"

Sensor::Sensor(QString name,
               QString label,
               size_t portNumber,
               size_t inputNumber,
               QString boardName,
               bool activeState,
               QColor color,
               QObject *parent) :
    QObject(parent),
    m_name(name),
    m_label(label),
    m_boardName(boardName),
    m_portNumber(portNumber),
    m_inputNumber(inputNumber),
    m_activeState(activeState),
    m_currentState(!m_activeState),
    m_color(color)
{
}

void Sensor::update(bool state)
{
    setCurrentState(state);
}

bool Sensor::getCurrentState() const
{
    return m_currentState;
}

void Sensor::setCurrentState(bool value)
{
    if(m_currentState != value)
    {
        m_currentState = value;

        if(m_currentState == m_activeState)
        {
            emit stateChanged(m_name, true);
        }
        else
        {
            emit stateChanged(m_name, false);
        }
    }
}

unsigned int Sensor::getPortNumber() const
{
    return m_portNumber;
}

unsigned int Sensor::getInputNumber() const
{
    return m_inputNumber;
}

QString Sensor::getName() const
{
    return m_name;
}

QString Sensor::getBoardName() const
{
    return m_boardName;
}

bool Sensor::getActiveState() const
{
    return m_activeState;
}

QColor Sensor::getColor() const
{
    return m_color;
}

bool Sensor::isEnable()
{
    return (m_activeState == m_currentState);
}

QString Sensor::getLabel() const
{
    return m_label;
}

QString Sensor::getSettings()
{
    QString sensorSettings = QStringLiteral("Label:") + m_label + QStringLiteral(";") +
            QStringLiteral("Name:") + m_name + QStringLiteral(";") +
            QStringLiteral("Board:") + m_boardName + QStringLiteral(";") +
            QStringLiteral("Port:") + QString::number(m_portNumber) + QStringLiteral(";") +
            QStringLiteral("Input:") + QString::number(m_inputNumber) + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(m_activeState) + QStringLiteral(";") +
            QStringLiteral("LedColor:") + QString::number(m_color.red()) + QStringLiteral(",") + QString::number(m_color.green()) + QStringLiteral(",") + QString::number(m_color.blue());
    return sensorSettings;
}

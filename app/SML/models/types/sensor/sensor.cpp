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
    this->setCurrentState(state);
}

bool Sensor::getCurrentState() const
{
    return this->m_currentState;
}

void Sensor::setCurrentState(bool value)
{
    if(this->m_currentState != value)
    {
        this->m_currentState = value;

        if(this->isEnable())
        {
            emit this->stateChanged(this->m_name, true);
        }
        else
        {
            emit this->stateChanged(this->m_name, false);
        }
    }
}

unsigned int Sensor::getPortNumber() const
{
    return this->m_portNumber;
}

unsigned int Sensor::getInputNumber() const
{
    return this->m_inputNumber;
}

QString Sensor::getName() const
{
    return this->m_name;
}

QString Sensor::getBoardName() const
{
    return this->m_boardName;
}

bool Sensor::getActiveState() const
{
    return this->m_activeState;
}

QColor Sensor::getColor() const
{
    return this->m_color;
}

bool Sensor::isEnable()
{
    return (this->m_activeState == this->m_currentState);
}

QString Sensor::getLabel() const
{
    return this->m_label;
}

QString Sensor::getSettings()
{
    QString sensorSettings = QStringLiteral("Label:") + this->m_label + QStringLiteral(";") +
            QStringLiteral("Name:") + this->m_name + QStringLiteral(";") +
            QStringLiteral("Board:") + this->m_boardName + QStringLiteral(";") +
            QStringLiteral("Port:") + QString::number(this->m_portNumber) + QStringLiteral(";") +
            QStringLiteral("Input:") + QString::number(this->m_inputNumber) + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(this->m_activeState) + QStringLiteral(";") +
            QStringLiteral("LedColor:") + QString::number(this->m_color.red()) +
                QStringLiteral(",") + QString::number(this->m_color.green()) +
                QStringLiteral(",") + QString::number(this->m_color.blue());
    return sensorSettings;
}

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
    m_activeStateLedColor(color)
{
}

bool Sensor::operator<(const Sensor &sensor)
{
    return this->m_uid < sensor.getUid();
}

bool Sensor::operator==(const Sensor &sensor)
{
    return this->m_uid == sensor.getUid();
}

void Sensor::updateInputState(bool state)
{
    this->setInputCurrentState(state);
}

bool Sensor::getInputCurrentState() const
{
    return m_inputCurrentState;
}

void Sensor::setInputCurrentState(bool value)
{
    if(m_inputCurrentState != value)
    {
        m_inputCurrentState = value;

        if(this->isEnable())
        {
            emit this->stateChanged(m_uid, true);
        }
        else
        {
            emit this->stateChanged(m_uid, false);
        }
    }
}

size_t Sensor::getPortNumber() const
{
    return m_portNumber;
}

size_t Sensor::getInputNumber() const
{
    return m_inputNumber;
}

QString Sensor::getUid() const
{
    return m_uid;
}

QString Sensor::getBoardName() const
{
    return m_boardName;
}

bool Sensor::getInputActiveState() const
{
    return m_inputActiveState;
}

QColor Sensor::getActiveStateLedColor() const
{
    return m_activeStateLedColor;
}

bool Sensor::isEnable()
{
    return (m_inputActiveState == m_inputCurrentState);
}

QString Sensor::getLabel() const
{
    return m_label;
}

QString Sensor::getSettings()
{
    QString sensorSettings = QStringLiteral("Label:") + m_label + QStringLiteral(";") +
            QStringLiteral("Uid:") + m_uid + QStringLiteral(";") +
            QStringLiteral("Board:") + m_boardName + QStringLiteral(";") +
            QStringLiteral("Port:") + QString::number(m_portNumber) + QStringLiteral(";") +
            QStringLiteral("Input:") + QString::number(m_inputNumber) + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(m_inputActiveState) + QStringLiteral(";") +
            QStringLiteral("CurrentState:") + QString::number(m_inputCurrentState) + QStringLiteral(";") +
            QStringLiteral("ActiveStateLedColor:") + m_activeStateLedColor.name();
    return sensorSettings;
}

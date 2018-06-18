#include "sensor.h"

Sensor::Sensor(QString code, const SettingsManager &sm, QObject *parent) :
    QObject(parent),
    m_code(code)
{
    initialize(sm);
}

void Sensor::initialize(const SettingsManager &sm)
{
    try
    {
        m_label = QVariant(sm.get(m_code, "Label")).toString();
        m_name  = QVariant(sm.get(m_code, "Name")).toString();
        m_portNumber = QVariant(sm.get(m_code, "PortNumber")).toUInt();
        m_inputNumber = QVariant(sm.get(m_code, "InputNumber")).toUInt();
        m_boardName = QVariant(sm.get(m_code, "BoardName")).toString();
        m_activeState = QVariant(sm.get(m_code, "ActiveState")).toBool();
        m_color = QColor(QVariant(sm.get(m_code, "Color")).toString());
        m_currentState = !m_activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки датчика " + m_code, e.what()).exec();
    }
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
    }

    if(m_currentState == m_activeState)
    {
        emit stateChanged(m_name, true);
    }
    else
    {
        emit stateChanged(m_name, false);
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


QString Sensor::getCode() const
{
    return m_code;
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
            QStringLiteral("ActiveState:") + QString::number(m_activeState);
    return sensorSettings;
}

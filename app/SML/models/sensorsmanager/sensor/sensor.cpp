#include "sensor.h"

Sensor::Sensor(QString _code,
               QString name,
               QString label,
               QString boardName,
               unsigned int portNumber,
               unsigned int inputNumber,
               bool activeState,
               QColor color) :
    m_code(_code),
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

Sensor::Sensor(QString code, const SettingsManager &sm) :
    m_code(code)
{
    setup(sm);
}

void Sensor::setup(const SettingsManager &sm)
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

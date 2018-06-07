#include "device.h"

Device::Device(QString code, const SettingsManager &sm) :
    m_code(code)
{
    initialize(sm);
}

Device::~Device()
{

}

void Device::initialize(const SettingsManager &sm)
{
    try
    {
        m_label = QVariant(sm.get(m_code, "Label")).toString();
        m_index = QVariant(sm.get(m_code, "Index")).toString();
        m_activeState = QVariant(sm.get(m_code, "ActiveState")).toBool();
        m_mask = QVariant(sm.get(m_code, "Mask")).toUInt();
        m_currentState = !m_activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + m_code, e.what() + m_code).exec();
    }
}

void Device::updateCurrentState(bool value)
{
    if(m_currentState != value)
    {
        m_currentState = value;
    }
}

bool Device::isEnable() const
{
    return (m_activeState == m_currentState);
}

QString Device::getLabel() const
{
    return m_label;
}

bool Device::getActiveState() const
{
    return m_activeState;
}

bool Device::getCurrentState() const
{
    return m_currentState;
}

byte Device::getMask() const
{
    return m_mask;
}

QString Device::getCode() const
{
    return m_code;
}

QString Device::getIndex() const
{
    return m_index;
}

#include "device.h"

Device::Device(QString name, const SettingsManager &sm, QObject *parent) :
    QObject(parent),
    m_name(name)
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
        m_label = QVariant(sm.get(m_name, "Label")).toString();
        m_index = QVariant(sm.get(m_name, "Index")).toString();
        m_activeState = QVariant(sm.get(m_name, "ActiveState")).toBool();
        m_mask = QVariant(sm.get(m_name, "Mask")).toUInt();
        m_currentState = !m_activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + m_name, e.what() + m_name).exec();
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

QString Device::getName() const
{
    return m_name;
}

QString Device::getIndex() const
{
    return m_index;
}

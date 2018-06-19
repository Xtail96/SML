#include "device.h"

Device::Device(QString name,
               QString label,
               QString index,
               bool activeState,
               int mask,
               QObject *parent) :
    QObject(parent),
    m_name(name),
    m_index(index),
    m_label(label),
    m_activeState(activeState),
    m_currentState(!m_activeState),
    m_mask(mask)
{

}

Device::~Device()
{

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

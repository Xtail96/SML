#include "device.h"

Device::Device(QString id, bool enabled, QString label):
    m_id(id),
    m_label(label),
    m_enabled(enabled)
{
    if (m_label.isEmpty())
        m_label = m_id;
}

Device::~Device()
{

}

bool Device::operator<(const Device &device)
{
    return this->m_id < device.getId();
}

bool Device::operator==(const Device &device)
{
    return this->m_id == device.getId();
}

bool Device::isEnabled() const
{
    return m_enabled;
}

QString Device::getLabel() const
{
    return m_label;
}

QString Device::getId() const
{
    return m_id;
}

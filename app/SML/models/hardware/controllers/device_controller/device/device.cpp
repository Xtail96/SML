#include "device.h"

Device::Device(QString settingsUid,
               QString uid,
               QString label,
               bool enable,
               QObject *parent) :
    QObject(parent),
    m_settingsUid(settingsUid),
    m_uid(uid),
    m_label(label),
    m_enable(enable)
{

}

Device::~Device()
{

}

bool Device::operator<(const Device &device)
{
    return this->m_uid < device.getUid();
}

bool Device::operator==(const Device &device)
{
    return this->m_uid == device.getUid();
}

void Device::setCurrentState(bool value, QMap<QString, QString> params)
{
    params = QMap<QString, QString>();

    if(m_enable != value)
    {
        m_enable = value;
        emit this->currentStateChanged(m_enable);
    }
}

bool Device::isEnable() const
{
    return m_enable;
}

QString Device::getLabel() const
{
    return m_label;
}

QString Device::getSettingsUId() const
{
    return m_settingsUid;
}

QString Device::getUid() const
{
    return m_uid;
}

QString Device::getSettings()
{
    QString deviceSettings = QStringLiteral("Label:") + m_label + QStringLiteral(";") +
            QStringLiteral("Uid:") + m_uid + QStringLiteral(";");
    return deviceSettings;
}

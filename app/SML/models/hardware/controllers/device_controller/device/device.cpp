#include "device.h"

Device::Device(QString settingsUid,
               QString uid,
               QString label,
               bool activeState,
               QObject *parent) :
    QObject(parent),
    m_settingsUid(settingsUid),
    m_uid(uid),
    m_label(label),
    m_activeState(activeState),
    m_currentState(!m_activeState)
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

    if(m_currentState != value)
    {
        m_currentState = value;

        if(m_currentState == m_activeState)
        {
            emit currentStateChanged(true);
        }
        else
        {
            emit currentStateChanged(false);
        }
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
            QStringLiteral("Uid:") + m_uid + QStringLiteral(";") +
            QStringLiteral("ActiveState:") + QString::number(m_activeState);
    return deviceSettings;
}

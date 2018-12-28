#include "support_device.h"

SupportDevice::SupportDevice(QString settingsUid,
                             QString label,
                             QString uid,
                             bool activeState,
                             QObject *parent) :
    Device(settingsUid, label, uid, activeState, parent)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}

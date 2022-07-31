#include "support_device.h"

SupportDevice::SupportDevice(QString settingsUid,
                             QString label,
                             QString uid,
                             bool enable,
                             QObject *parent) :
    Device(settingsUid, label, uid, enable, parent)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}

#include "support_device.h"

SupportDevice::SupportDevice(QString settingsUid, QString label, QString uid, bool activeState, byte mask, QObject *parent) :
    Device(settingsUid, label, uid, activeState, mask, parent)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}

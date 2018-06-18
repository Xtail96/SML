#include "supportdevice.h"

SupportDevice::SupportDevice(QString code, const SettingsManager &sm, QObject *parent) :
    Device(code, sm, parent)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}

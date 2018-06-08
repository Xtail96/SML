#include "supportdevice.h"

SupportDevice::SupportDevice(QString code, const SettingsManager &sm) :
    Device(code, sm)
{

}

QStringList SupportDevice::getParams()
{
    return QStringList();
}

#ifndef SUPPORTDEVICE_H
#define SUPPORTDEVICE_H

#include "models/devicesmanager/device/device.h"

class SupportDevice : public Device
{
public:
    SupportDevice(QString code, const SettingsManager &sm = SettingsManager());
    QStringList getParams() override;
};

#endif // SUPPORTDEVICE_H

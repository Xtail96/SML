#ifndef SUPPORTDEVICE_H
#define SUPPORTDEVICE_H

#include "models/types/device/device.h"

class SupportDevice : public Device
{
public:
    SupportDevice(QString settingsUid,
                  QString label,
                  QString uid,
                  bool activeState,
                  QObject *parent = nullptr);
    QStringList getParams() override;
};

#endif // SUPPORTDEVICE_H

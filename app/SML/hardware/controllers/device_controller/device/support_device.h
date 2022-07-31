#ifndef SUPPORTDEVICE_H
#define SUPPORTDEVICE_H

#include "./device.h"

class SupportDevice : public Device
{
public:
    SupportDevice(QString settingsUid,
                  QString label,
                  QString uid,
                  bool enable,
                  QObject *parent = nullptr);
    QStringList getParams() override;
};

#endif // SUPPORTDEVICE_H

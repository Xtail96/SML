#ifndef SUPPORTDEVICE_H
#define SUPPORTDEVICE_H

#include "models/types/device/device.h"

class SupportDevice : public Device
{
public:
    SupportDevice(QString name, QString label, QString index, bool activeState, int mask, QObject *parent = nullptr);
    QStringList getParams() override;
};

#endif // SUPPORTDEVICE_H

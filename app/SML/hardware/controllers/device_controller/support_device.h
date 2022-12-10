#ifndef SUPPORTDEVICE_H
#define SUPPORTDEVICE_H

#include "./device.h"

class SupportDevice : public Device
{
public:
    SupportDevice(QString id, bool enabled, QString label = "");
};

#endif // SUPPORTDEVICE_H

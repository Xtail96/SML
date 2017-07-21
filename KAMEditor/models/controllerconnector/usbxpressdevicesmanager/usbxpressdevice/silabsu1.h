#ifndef SILABSU1_H
#define SILABSU1_H
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.h"
#include "models/machinetool/machinetool.h"

class SiLabsU1 : public UsbXpressDevice
{
public:
    SiLabsU1(MachineTool *machineTool);
    int receiveData();
    int sendData();
};

#endif // SILABSU1_H

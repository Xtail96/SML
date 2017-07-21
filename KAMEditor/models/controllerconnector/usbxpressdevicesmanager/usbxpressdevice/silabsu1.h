#ifndef SILABSU1_H
#define SILABSU1_H
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.h"

class SiLabsU1 : public UsbXpressDevice
{
public:
    SiLabsU1(std::string deviceName = "semil");
    int receiveData();
    int sendData();
};

#endif // SILABSU1_H

#ifndef USBXPRESSDEVICEMANAGER_H
#define USBXPRESSDEVICEMANAGER_H

#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/silabsu1.h"

#ifdef Q_OS_WIN
class UsbXpressDeviceManager
{
private:
    SiLabsU1* u1;
public:
    UsbXpressDeviceManager(std::string deviceName);
    ~UsbXpressDeviceManager();
    //void connectWithSiLabsDevice();

    SiLabsU1* getU1() const;
};
#endif

#endif // USBXPRESSDEVICEMANAGER_H

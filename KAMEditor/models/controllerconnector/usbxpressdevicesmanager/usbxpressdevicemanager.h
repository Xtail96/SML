#ifndef USBXPRESSDEVICEMANAGER_H
#define USBXPRESSDEVICEMANAGER_H

#ifdef Q_OS_WIN
#include "models/machinetool/machinetool.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/silabsu1.h"

class UsbXpressDeviceManager
{
private:
    MachineTool* machineTool;
    SiLabsU1* u1;
public:
    UsbXpressDeviceManager(MachineTool *_machineTool);
    ~UsbXpressDeviceManager();
    void connectWithSiLabsDevice();

    SiLabsU1* getU1() const;
};
#endif

#endif // USBXPRESSDEVICEMANAGER_H

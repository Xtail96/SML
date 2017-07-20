#ifndef DEBUGMODULE_H
#define DEBUGMODULE_H

#include <vector>

#include "models/machinetool/machinetool.h"
#include "models/controllerconnector/usbdevicesmanager/usbdevice/usbdevice.h"
#include "models/machinetool/devicesmanager/device/device.h"
#include "models/machinetool/sensorsmanager/sensor/sensor.h"

class DebugModule
{
    /*UsbDevice usbDevice;

    std::vector< std::shared_ptr<Sensor> > inputs;

    std::vector< std::shared_ptr<Device> > outputs;*/

public:
    DebugModule(MachineTool *machineTool);
    ~DebugModule();

    int checkConnection();
    bool waitForSignal();
    bool switchDeviceOn();
    bool switchDeviceOff();
};

#endif // DEBUGMODULE_H

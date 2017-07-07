#ifndef DEBUGMODULE_H
#define DEBUGMODULE_H

#include <vector>

#include "machinetool/machinetool.h"
#include "machinetool/mcuLinksProvider/usbDevice/usbdevice.h"
#include "machinetool/components/devices/device.h"
#include "machinetool/components/sensors/sensor.h"

class DebugModule
{
    UsbDevice usbDevice;

    uint16_t machineToolVendorId;

    uint16_t machineToolProductId;

    std::vector< std::shared_ptr<Sensor> > inputs;

    std::vector< std::shared_ptr<Device> > outputs;

public:
    DebugModule(MachineTool *machineTool);
    ~DebugModule();

    int checkConnection();
    bool waitForSignal();
    bool switchDeviceOn();
    bool switchDeviceOff();
    UsbDevice *getUsbConnector();
};

#endif // DEBUGMODULE_H

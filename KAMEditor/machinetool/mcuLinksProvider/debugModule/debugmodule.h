#ifndef DEBUGMODULE_H
#define DEBUGMODULE_H

#include <vector>

#include "machinetool/machinetool.h"
#include "machinetool/mcuLinksProvider/usbConnector/usbconnector.h"
#include "machinetool/components/devices/device.h"
#include "machinetool/components/sensors/sensor.h"

#define VENDOR_ID  0x10c4 //0x125f
#define PRODUCT_ID 0xea61 //0x385a
#define USB_DEBUG_LEVEL 1
#define DATA_SIZE 64

class DebugModule
{
    UsbConnector usbConnector;
    std::vector< std::shared_ptr<Sensor> > inputs;
    std::vector< std::shared_ptr<Device> > outputs;

public:
    DebugModule(MachineTool *machineTool);
    ~DebugModule();

    int checkConnection();
    bool waitForSignal();
    bool switchDeviceOn();
    bool switchDeviceOff();
    UsbConnector *getUsbConnector();
};

#endif // DEBUGMODULE_H

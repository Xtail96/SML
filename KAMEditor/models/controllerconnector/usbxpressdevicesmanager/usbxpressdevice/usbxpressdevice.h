#ifndef USBXPRESSDEVICE_H
#define USBXPRESSDEVICE_H

#include <QDebug>
#include <memory>

// usbxpress
#include "dependencies.h"


#define VENDOR_ID  0x10c4
#define PRODUCT_ID 0xea61

class UsbXpressDevice
{
public:
    HANDLE siDeviceHandle;
    UsbXpressDevice();
    void initialize();
};

#endif // USBXPRESSDEVICE_H

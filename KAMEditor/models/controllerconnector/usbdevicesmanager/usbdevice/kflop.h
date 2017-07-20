#ifndef KFLOP_H
#define KFLOP_H

#include "usbdevice.h"

class KFlop : public UsbDevice
{
public:
    KFlop(uint16_t _vendorId, uint16_t _productId);
};

#endif // KFLOP_H

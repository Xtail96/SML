#ifndef U1_H
#define U1_H

#include "usbdevice.h"

class U1 : public UsbDevice
{
public:
    U1(uint16_t _vendorId, uint16_t _productId);
};

#endif // U1_H

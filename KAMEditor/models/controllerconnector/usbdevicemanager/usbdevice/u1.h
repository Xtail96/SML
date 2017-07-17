#ifndef U1_H
#define U1_H

#include "usbdevice.h"

class U1 : public UsbDevice
{
public:
    U1(uint16_t _vendorId, uint16_t _productId);
    virtual void receiveData() override;
    virtual void sendData() override;
    void displayData(unsigned char *data, unsigned int dataSize);
    void displayDeviceInfromation();
};

#endif // U1_H

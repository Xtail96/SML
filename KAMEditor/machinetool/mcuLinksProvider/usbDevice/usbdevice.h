#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <vector>
#include <QDebug>

#include "dependencies.h"

class UsbDevice
{
private:
    libusb_context *context = NULL;
    libusb_device *device = NULL;
    libusb_device_handle *deviceHandle = NULL;

    void initialize_libusb();
    void initializeDevice(uint16_t vid, uint16_t pid);
    libusb_device* findDevice(uint16_t vid, uint16_t pid, libusb_device** devices, size_t N);
    libusb_device_handle* openDevice(libusb_device* device);

public:
    UsbDevice(uint16_t vendorId, uint16_t productId);
    ~UsbDevice();
};

#endif // USBDEVICE_H

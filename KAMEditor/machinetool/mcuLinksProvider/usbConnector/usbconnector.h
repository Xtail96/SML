#ifndef USBCONNECTOR_H
#define USBCONNECTOR_H

#include <vector>

#include <QDebug>

#include "libusb/include/libusb.h"

class usbConnector
{
    libusb_context *context;
    int initializationCode;

    libusb_device **devicesList;
    size_t deviceCount;

    libusb_device *currentDevice;
    libusb_device_handle *currentDeviceHandler;
    libusb_device_descriptor currentDeviceDescriptor;

    uint16_t currentVendorId;
    uint16_t currentProductId;


    std::vector< std::pair<uint16_t, uint16_t> > devicesVidPid;

    bool isInitialize;
    bool isOpen;

public:
    usbConnector();
    ~usbConnector();

    void initialize();
    int open(uint16_t vendorId, uint16_t productId);

    std::vector<std::pair<uint16_t, uint16_t> > getDevicesVidPid() const;
    void setDevicesVidPid(const std::vector<std::pair<uint16_t, uint16_t> > &value);
    uint16_t getCurrentVendorId() const;
    void setCurrentVendorId(const uint16_t &value);
    uint16_t getCurrentProductId() const;
    void setCurrentProductId(const uint16_t &value);
    libusb_device_handle *getCurrentDeviceHandler() const;
};

#endif // USBCONNECTOR_H

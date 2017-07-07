#include "usbconnector.h"

std::vector<std::pair<uint16_t, uint16_t> > usbConnector::getDevicesVidPid() const
{
    return devicesVidPid;
}

void usbConnector::setDevicesVidPid(const std::vector<std::pair<uint16_t, uint16_t> > &value)
{
    devicesVidPid = value;
}

uint16_t usbConnector::getCurrentVendorId() const
{
    return currentVendorId;
}

void usbConnector::setCurrentVendorId(const uint16_t &value)
{
    currentVendorId = value;
}

uint16_t usbConnector::getCurrentProductId() const
{
    return currentProductId;
}

void usbConnector::setCurrentProductId(const uint16_t &value)
{
    currentProductId = value;
}

libusb_device_handle *usbConnector::getCurrentDeviceHandler() const
{
    return currentDeviceHandler;
}

usbConnector::usbConnector()
{

    context = NULL;

    initializationCode = -1;

    currentVendorId = 0;
    currentProductId = 0;
    currentDeviceHandler = NULL;
    currentDevice = NULL;
    currentDeviceDescriptor = {0};

    deviceCount = 0;
    devicesVidPid = {};

    isInitialize = false;
    isOpen = false;
}

usbConnector::~usbConnector()
{
    if(isInitialize)
    {
        if(isOpen)
        {
            libusb_close(currentDeviceHandler);
        }
        libusb_free_device_list(devicesList, 1);
        libusb_exit(context);
    }
}

void usbConnector::initialize()
{
    initializationCode = libusb_init(&context);
    qDebug() << "libusb_code =" << initializationCode << endl;
    if(initializationCode == 0)
    {
        deviceCount = libusb_get_device_list(context, &devicesList);
        qDebug() << "Found" << deviceCount << "devices" << endl;
        if(deviceCount > 0)
        {
            for(size_t i = 0; i < deviceCount; i++)
            {
                libusb_device *device = devicesList[i];
                libusb_device_descriptor descriptor = {0};

                libusb_get_device_descriptor(device, &descriptor);
                qDebug() << "vid:pid =" << descriptor.idVendor << ":" << descriptor.idProduct;

                devicesVidPid.push_back(std::make_pair(descriptor.idVendor, descriptor.idProduct));
            }
        }

        isInitialize = true;
    }
}

int usbConnector::open(uint16_t vendorId, uint16_t productId)
{
    int openCode = -1;
    if(isInitialize)
    {
        for(size_t i = 0; i < deviceCount; i++)
        {
            libusb_device *device = devicesList[i];
            libusb_device_descriptor descriptor = {0};

            libusb_get_device_descriptor(device, &descriptor);

            if((descriptor.idVendor == vendorId) && (descriptor.idProduct == productId))
            {
                currentDevice = device;
                currentDeviceDescriptor = descriptor;
                openCode = libusb_open(currentDevice, &currentDeviceHandler);
                if(openCode == 0)
                {
                    qDebug() << "Device is open" << endl;
                    isOpen = true;
                }
                else
                {
                    isOpen = false;
                    qDebug() << "Device is not open" << openCode << endl;
                }
                break;
            }
        }
    }
    return openCode;
}

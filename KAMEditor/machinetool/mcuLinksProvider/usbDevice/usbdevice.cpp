#include "usbdevice.h"

UsbDevice::UsbDevice(uint16_t vendorId, uint16_t productId)
{
    initialize_libusb();
    initializeDevice(vendorId, productId);
    claimInterface();
}

UsbDevice::~UsbDevice()
{
    releaseInterface();
    libusb_close(deviceHandle);
    libusb_exit(context);
}

void UsbDevice::initialize_libusb()
{
    int code = libusb_init(&context);

    if (code != 0)
    {
        std::string errMsg = "libusb initialization error (code " + std::to_string(code) + ")";
        qDebug() << QString::fromStdString(errMsg);
        throw std::runtime_error(errMsg);
    }
}

void UsbDevice::initializeDevice(uint16_t vid, uint16_t pid)
{
    libusb_device** devices = NULL;
    size_t devicesCount = libusb_get_device_list(context, &devices);

    try
    {
        device = findDevice(vid, pid, devices, devicesCount);
        deviceHandle = openDevice(device);

        libusb_free_device_list(devices, 1);
    }
    catch (std::runtime_error e)
    {
        qDebug() << e.what();
        libusb_free_device_list(devices, 1);

        throw;
    }
}

libusb_device* UsbDevice::findDevice(uint16_t vid, uint16_t pid, libusb_device** devices, size_t N)
{
    for (size_t i = 0; i < N; i++)
    {
        libusb_device *dev = devices[i];
        libusb_device_descriptor descriptor;

        int code = libusb_get_device_descriptor(dev, &descriptor);

        if ((code == 0) && (descriptor.idVendor == vid) && (descriptor.idProduct == pid))
            return dev;
    }

    std::string errMsg = "No device found with vid=" + std::to_string(vid) + ", pid=" + std::to_string(pid);
    throw std::runtime_error(errMsg);
    //return NULL;
}

libusb_device_handle* UsbDevice::openDevice(libusb_device *device)
{
    libusb_device_handle* handle;
    int code = libusb_open(device, &handle);

    if (code != 0)
    {
        throw std::runtime_error("Failed to open device");
    }

    return handle;
}

void UsbDevice::claimInterface(int interfaceNumber)
{
    int code = libusb_claim_interface(deviceHandle, interfaceNumber);
    if(code < 0)
    {
        std::string errMsg = "Interface Error " + code;
        throw std::runtime_error(errMsg);
    }
}

void UsbDevice::releaseInterface(int interfaceNumber)
{
    int code = libusb_release_interface(deviceHandle, interfaceNumber);
    if(code < 0)
    {
        std::string errMsg = "Interface Error " + code;
        throw std::runtime_error(errMsg);
        qDebug() << QString::fromStdString(errMsg) << endl;
    }
}

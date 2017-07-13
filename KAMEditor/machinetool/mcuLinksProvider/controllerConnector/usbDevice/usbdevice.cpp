#include "usbdevice.h"

UsbDevice::UsbDevice(uint16_t vendorId, uint16_t productId)
{
    initialize_libusb();
    initializeDevice(vendorId, productId);
    requestInterface();
}

UsbDevice::~UsbDevice()
{
    freeInterface();
    libusb_close(deviceHandle);
    libusb_exit(context);
}

void UsbDevice::receiveData()
{
//    struct libusb_config_descriptor *config;
//    struct libusb_endpoint_descriptor **endpoints;
//    if(libusb_get_endpoint_descriptor(device, endpoints) == 0)
//    {
//        int le = endpoints->bEndpointAddress;
//        qDebug() << le << endl;
//    }
    unsigned char* data = new unsigned char[64];
    int data_size = 64;
    int transferred = 0;
    unsigned int timeout = 0;
    qDebug() << "origin = " << *data << endl;
    int code = libusb_interrupt_transfer(deviceHandle, endPointOut, data, data_size, &transferred, timeout);
    qDebug() << "transferred" << transferred << "bytes" << endl;
    if(code == 0)
    {
        qDebug() << *data << endl;
    }
    else
    {
        std::string errMsg = libusb_error_name(code);
        QString errorDescription = QString::fromStdString(errMsg);
        qDebug() << errorDescription << endl;
    }
    delete[] data;
    qDebug() << "successful delete" << endl;
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

void UsbDevice::requestInterface(int interfaceNumber)
{
    int code = libusb_set_configuration(deviceHandle, 1);
    if(code != 0)
    {
        std::string errMsg = "Can not set configuration" + std::to_string(code);
        throw std::runtime_error(errMsg);
    }
    code = libusb_claim_interface(deviceHandle, interfaceNumber);
    if(code != 0)
    {
        //std::string errMsg = "Interface Error " + std::to_string(code);
        std::string errMsg = libusb_error_name(code);
        throw std::runtime_error(errMsg);
    }
}

void UsbDevice::freeInterface(int interfaceNumber)
{
    int code = libusb_release_interface(deviceHandle, interfaceNumber);
    if(code != 0)
    {
        std::string errMsg = "Interface Error " + std::to_string(code);
        throw std::runtime_error(errMsg);
        qDebug() << QString::fromStdString(errMsg) << endl;
    }
}

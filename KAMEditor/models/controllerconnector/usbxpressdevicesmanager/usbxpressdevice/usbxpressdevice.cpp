#include "usbxpressdevice.h"

UsbXpressDevice::UsbXpressDevice(std::string deviceName)
{
    initialize(deviceName);
}

UsbXpressDevice::~UsbXpressDevice()
{
   free();
}

void UsbXpressDevice::initialize(std::string deviceName)
{
    DWORD num;
    int siDeviceNumber = -1;

    SI_STATUS code = SI_GetNumDevices(&num);
    if(code == SI_SUCCESS)
    {
        siDeviceNumber = findDevice(deviceName, num);
        if(siDeviceNumber > -1)
        {
            setupSiLabsDevice(siDeviceNumber);
        }
        else
        {
            std::string errMsg = "Device not found";
            qDebug() << QString::fromStdString(errMsg);
            throw std::runtime_error(errMsg);
        }
    }
    else
    {
        std::string errMsg = "initialization error (code " + std::to_string(code) + ")";
        qDebug() << QString::fromStdString(errMsg);
        throw std::runtime_error(errMsg);
    }
}

void UsbXpressDevice::free()
{
    SI_Close(siDeviceHandle);
}

int UsbXpressDevice::findDevice(std::string deviceName, DWORD count)
{
    int siDeviceNumber = -1;
    SI_DEVICE_STRING siDeviceString;

    for(unsigned int i = 0; i < count; i++)
    {
        SI_GetProductString(i, &siDeviceString, 0);
        qDebug() << siDeviceString;
        std::string siDeviceStringStd = std::string(siDeviceString);
        if(siDeviceStringStd == deviceName)
        {
            siDeviceNumber = i;
            break;
        }
    }
    return siDeviceNumber;
}

void UsbXpressDevice::setupSiLabsDevice(int silabsDeviceNumber)
{
    SI_STATUS code = SI_Open(silabsDeviceNumber, &siDeviceHandle);
    if(code == SI_SUCCESS)
    {
        SI_SetTimeouts(500, 500);
        SI_FlushBuffers(siDeviceHandle, 1, 1);
    }
    else
    {
        std::string errMsg = "Open Error";
        qDebug() << QString::fromStdString(errMsg);
        throw std::runtime_error(errMsg);
    }
}

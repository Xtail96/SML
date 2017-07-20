#include "usbxpressdevice.h"

UsbXpressDevice::UsbXpressDevice()
{
    initialize();
}

void UsbXpressDevice::initialize()
{
    DWORD num;
    int siDeviceNumber = -1;
    SI_DEVICE_STRING siDeviceString;

    SI_STATUS code = SI_GetNumDevices(&num);
    if(code == SI_SUCCESS)
    {
        for(unsigned int i = 0; i < num; i++)
        {
            SI_GetProductString(i, &siDeviceString, 0);
            qDebug() << siDeviceString;
            std::string siDeviceStringStd = std::string(siDeviceString);
            if(siDeviceStringStd == "semir" || siDeviceStringStd == "semil")
            {
                siDeviceNumber = i;
                break;
            }
            else
            {
                std::string errMsg = "Unknown Device";
                qDebug() << QString::fromStdString(errMsg);
                throw std::runtime_error(errMsg);
            }
        }

        if(siDeviceNumber > -1)
        {
            code = SI_Open(siDeviceNumber, &siDeviceHandle);
            if(code == SI_SUCCESS)
            {
                /*SI_SETTIMEOUTS(500, 500);
                SI_FLUSHBUFFERS(siDeviceHandle, 1, 1);*/
            }
            else
            {
                std::string errMsg = "Open Error";
                qDebug() << QString::fromStdString(errMsg);
                throw std::runtime_error(errMsg);
            }
        }
        else
        {
            std::string errMsg = "Connection Error";
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

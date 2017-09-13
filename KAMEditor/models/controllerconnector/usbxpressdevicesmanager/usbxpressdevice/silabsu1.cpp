#include "silabsu1.h"

#ifdef Q_OS_WIN
SiLabsU1::SiLabsU1(std::string deviceName) :
    UsbXpressDevice(deviceName)
{

}

SiLabsU1::~SiLabsU1()
{
    free();
}

byte_array SiLabsU1::receiveData(unsigned int packetSize)
{
    try
    {
        byte_array data(packetSize, 0);
        DWORD transferred = 0;
        requestReceiving();
        SI_STATUS code = SI_Read(siDeviceHandle, data.data(), data.size(), &transferred);
        if(code != 0)
        {
            std::string errMsg = libusb_error_name(code);
            errMsg+=" Не могу прочитать данные";
            throw std::runtime_error(errMsg);
        }

        // если число запрошенных и полученных байт не совпадает, ошибка
        if (packetSize != transferred)
        {
            std::string errMsg = libusb_error_name(code);
            errMsg += " Получено " + std::to_string(transferred) + " байт ";
            errMsg += " из " + std::to_string(packetSize);

            throw std::runtime_error(errMsg);
        }
        return data;
    }
    catch(std::runtime_error e)
    {
        throw;
    }
}

void SiLabsU1::requestReceiving()
{
    byte_array data = { GET_MCU_STATE };
    sendData(data);
}

void SiLabsU1::sendData(const byte_array& data)
{
    byte* rawDataPtr = const_cast<byte*>(data.data());
    DWORD transferred = 0;
    SI_STATUS code = SI_Write(siDeviceHandle, rawDataPtr, data.size(), &transferred);
    if(code != 0)
    {
        std::string errMsg = "Не могу отправить запрос на получение данных о станке" + std::to_string(code);
        throw std::runtime_error(errMsg);
    }
    // если число запрошенных и отправленных байт не совпадает, ошибка
    if (data.size() != transferred)
    {
        std::string errMsg = " Отправлено " + std::to_string(transferred) + " байт ";
        errMsg += " из " + std::to_string(data.size());
        throw std::runtime_error(errMsg);
    }
}

void SiLabsU1::displayData(const byte_array& data)
{
    for(byte b : data)
    {
        qDebug() << QString::number(b, 16);
    }
}
#endif

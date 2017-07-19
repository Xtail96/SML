#include "u1.h"

U1::U1(uint16_t _vendorId, uint16_t _productId) :
    UsbDevice(_vendorId, _productId)
{

}

byte_array U1::receiveData(int packetSize)
{
    displayDeviceInformation();

    if (packetSize == 0)
        packetSize = libusb_get_max_packet_size(device, endPointIn);

    try
    {
        byte_array data(packetSize, 0);
        int transferred = 0;

        requestReceiving();

        int code = libusb_bulk_transfer(deviceHandle, endPointIn, data.data(), data.size(), &transferred, RECV_TIMEOUT);
        qDebug() << "transferred" << transferred << "bytes" << endl;

        if(code == 0)
        {
            clearEndpoint(endPointIn);
        }
        else
        {
            std::string errMsg = libusb_error_name(code);
            errMsg+=" Не могу прочитать данные";
            throw std::runtime_error(errMsg);
        }

        // если число запрошенных и полученных байт не совпадает, ошибка
        if (packetSize != transferred)
        {
            std::string errMsg = libusb_error_name(code);
            errMsg += " Отправлено " + std::to_string(transferred) + " байт ";
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

int U1::sendData(const byte_array& data)
{
    displayDeviceInformation();

    int transferred = 0;
    byte* rawDataPtr = const_cast<byte*>(data.data());

    int code = libusb_bulk_transfer(deviceHandle, endPointOut, rawDataPtr, data.size(), &transferred, SEND_TIMEOUT);

    qDebug() << "transferred" << transferred << "bytes" << endl;

    if(code == 0)
    {
        clearEndpoint(endPointOut);
    }
    else
    {
        std::string errMsg = libusb_error_name(code);
        errMsg += " Не могу отправить запрос на получение данных о станке";
        throw std::runtime_error(errMsg);
    }

    return transferred;
}

void U1::requestReceiving()
{
    byte_array data = { GET_MCU_STATE };

    sendData(data);
}

void U1::clearEndpoint(int endPoint)
{
    int code = libusb_clear_halt(deviceHandle, endPoint);
    if(code != 0)
    {
        std::string errMsg = libusb_error_name(code);
        QString errorDescription = QString::fromStdString(errMsg);
        qDebug() << errorDescription << endl;
    }
}

void U1::displayData(unsigned char *data, unsigned int dataSize)
{
    for(unsigned int i = 0; i < dataSize; i++)
    {
        qDebug() << QString::number(data[i], 16);
    }
}

void U1::displayDeviceInformation()
{
    uint8_t portNumber = libusb_get_port_number(device);
    qDebug() << "Port number = " << portNumber;
    uint8_t busNumber = libusb_get_bus_number(device);
    qDebug() << "Bus number = " << busNumber;
    uint8_t deviceAddress = libusb_get_device_address(device);
    qDebug() << "Device address = " << deviceAddress;
    int deviceSpeed = libusb_get_device_speed(device);
    qDebug() << "Device speed = " << deviceSpeed;
}

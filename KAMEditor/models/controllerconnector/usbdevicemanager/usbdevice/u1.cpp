#include "u1.h"

unsigned char U1::getGET_MCU_STATE() const
{
    return GET_MCU_STATE;
}

U1::U1(uint16_t _vendorId, uint16_t _productId) :
    UsbDevice(_vendorId, _productId)
{

}

std::vector<unsigned char> U1::receiveData()
{
    displayDeviceInfromation();

    int maxPacketSize = libusb_get_max_packet_size(device, endPointIn);
    qDebug() << "maxPacketSize = " << maxPacketSize;

    int packetSize = std::max(maxPacketSize, 8);
    std::vector<unsigned char> params(packetSize - 1, 0);
    // отправляем запрос на получение информации о станке
    try
    {
        sendData(GET_MCU_STATE, params);

        unsigned char *data = new unsigned char[packetSize];
        for(int i = 0; i < packetSize; i++)
        {
            data[i] = 0;
        }

        int transferred = 0;
        unsigned int timeout = 5000;

        // если отправка запроса прошла без ошибок получаем данные
        int code = libusb_bulk_transfer(deviceHandle, endPointIn, data, packetSize, &transferred, timeout);
        qDebug() << "transferred" << transferred << "bytes" << endl;
        if(code == 0)
        {
            clearEndpoint(endPointIn);
            clearEndpoint(endPointOut);

            for(int i = 0; i < packetSize; i++)
            {
                params[i] = data[i];
            }
            return params;
        }
        else
        {
            std::string errMsg = libusb_error_name(code);
            errMsg+=" Не могу прочитать данные";
            throw std::runtime_error(errMsg);
        }
    }
    catch(std::runtime_error e)
    {
        throw;
    }
}

void U1::sendData(unsigned char actionId, std::vector<unsigned char> params)
{
    displayDeviceInfromation();

    int transferred = 0;
    unsigned int timeout = 5000;


    unsigned int dataSize = sizeof(actionId) + params.size();
    unsigned char* data = makePacket(actionId, params, dataSize);
    int code = libusb_bulk_transfer(deviceHandle, endPointOut, data, dataSize, &transferred, timeout);
    delete[] data;


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
}

unsigned char* U1::makePacket(unsigned char actionId, std::vector<unsigned char> params, unsigned int &dataSize)
{
    if(dataSize < params.size())
    {
        dataSize = sizeof(actionId) + params.size();
    }
    unsigned char* dataPacket = new unsigned char[dataSize];
    dataPacket[0] = actionId;
    for(unsigned int i = 1; i < dataSize; i++)
    {
        dataPacket[i] = params[i - 1];
    }
    return dataPacket;
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

void U1::displayDeviceInfromation()
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

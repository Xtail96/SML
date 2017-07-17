#include "u1.h"

U1::U1(uint16_t _vendorId, uint16_t _productId) :
    UsbDevice(_vendorId, _productId)
{

}

void U1::receiveData()
{
    //    struct libusb_config_descriptor *config;
    //    struct libusb_endpoint_descriptor **endpoints;
    //    if(libusb_get_endpoint_descriptor(device, endpoints) == 0)
    //    {
    //        int le = endpoints->bEndpointAddress;
    //        qDebug() << le << endl;
    //    }
    uint8_t portNumber = libusb_get_port_number(device);
    qDebug() << "Port number = " << portNumber;
    uint8_t busNumber = libusb_get_bus_number(device);
    qDebug() << "Bus number = " << busNumber;
    uint8_t deviceAddress = libusb_get_device_address(device);
    qDebug() << "Device address = " << deviceAddress;
    int deviceSpeed = libusb_get_device_speed(device);
    /*std::string deviceSpeedString = libusb_speed_name(deviceSpeed);
    QString qDeviceSpeed = QString::fromStdString(deviceSpeedString);*/
    qDebug() << "Device speed = " << deviceSpeed;


    int packetSize = libusb_get_max_packet_size(device, endPointOut);
    qDebug() << "maxPacketSize = " << packetSize;
    unsigned char data[64];
    int data_size = packetSize;
    for(int i = 0; i < data_size; i++)
    {
        data[i] = i;
    }
    int transferred = 0;
    unsigned int timeout = 0;
    int code = libusb_interrupt_transfer(deviceHandle, endPointOut, data, data_size, &transferred, timeout);
    qDebug() << "transferred" << transferred << "bytes" << endl;
    if(code == 0)
    {
        displayData(data, data_size);
        code = libusb_clear_halt(deviceHandle, endPointOut);
        if(code != 0)
        {
            std::string errMsg = libusb_error_name(code);
            QString errorDescription = QString::fromStdString(errMsg);
            qDebug() << errorDescription << endl;
        }
    }
    else
    {
        std::string errMsg = libusb_error_name(code);
        QString errorDescription = QString::fromStdString(errMsg);
        qDebug() << errorDescription << endl;
    }
}

void U1::sendData()
{

}

void U1::displayData(unsigned char *data, unsigned int dataSize)
{
    for(unsigned int i = 0; i < dataSize; i++)
    {
        qDebug() << data[i];
    }
}

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

void U1::sendData()
{

}

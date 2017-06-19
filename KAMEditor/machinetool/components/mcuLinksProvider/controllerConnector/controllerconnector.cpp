#include "controllerconnector.h"
ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

ControllerConnector::~ControllerConnector()
{
    serialPort->close();
}

void ControllerConnector::send()
{

}

void ControllerConnector::recieved()
{
    QByteArray serialPortByteArray;
    serialPortByteArray = serialPort->readAll();
    qDebug() << serialPortByteArray << endl;
}

ControllerConnector::ControllerConnector()
{
    serialPort = new QSerialPort(this);
    serialPort->setPortName("com4");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(recieved()));
}

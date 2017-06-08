#include "controllerconnector.h"
ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

void ControllerConnector::send()
{

}

ControllerConnector::ControllerConnector()
{
    serialPort.setBaudRate(2400);
    serialPort.setBreakEnabled(true);
    serialPort.setCurrentReadChannel(1);
    serialPort.setCurrentWriteChannel(2);
    serialPort.setReadBufferSize(1024);
    serialPort.setPortName("U1");
}

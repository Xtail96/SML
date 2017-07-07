#include "debugmodule.h"

UsbConnector* DebugModule::getUsbConnector()
{
    return &usbConnector;
}

DebugModule::DebugModule(MachineTool *machineTool)
{
    inputs = machineTool->getSensors();
    outputs = machineTool->getDevices();
}

DebugModule::~DebugModule()
{

}

int DebugModule::checkConnection()
{
    int connectionCode = -1;
    usbConnector.initialize();
    //int openCode = usbConnector.open(VENDOR_ID, PRODUCT_ID);
    int openCode = usbConnector.open(0x125f, 0x385a);
    if(openCode == 0 && usbConnector.getCurrentDeviceHandler() != NULL)
    {
        connectionCode = openCode;
    }
    return connectionCode;
}

bool DebugModule::waitForSignal()
{

}

bool DebugModule::switchDeviceOn()
{

}

bool DebugModule::switchDeviceOff()
{

}

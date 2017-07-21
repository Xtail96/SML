#include "silabsu1.h"

SiLabsU1::SiLabsU1(MachineTool *machineTool) :
    UsbXpressDevice(machineTool->getName())
{

}

int SiLabsU1::receiveData()
{
    return 0;
}

int SiLabsU1::sendData()
{
    return 0;
}

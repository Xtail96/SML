#include "debugmodule.h"

DebugModule::DebugModule(MachineTool *machineTool)
{

}

DebugModule::~DebugModule()
{

}

int DebugModule::checkConnection()
{
    return 0;
}

bool DebugModule::waitForSignal()
{
    return true;
}

bool DebugModule::switchDeviceOn()
{
    return true;
}

bool DebugModule::switchDeviceOff()
{
    return true;
}

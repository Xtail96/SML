#include "device.h"

Device::Device(unsigned int _output, std::string _name, unsigned int _pause, bool _isActive, bool _isOn) :
    output(_output), name(_name), pause(_pause), isActive(_isActive), isOn(_isOn), errorCode(0)
{

}

unsigned int Device::getOutput() const
{
    return output;
}

void Device::setOutput(unsigned int value)
{
    output = value;
}

std::string Device::getName() const
{
    return name;
}

void Device::setName(const std::string &value)
{
    name = value;
}

unsigned int Device::getPause() const
{
    return pause;
}

void Device::setPause(unsigned int value)
{
    pause = value;
}

bool Device::getIsActive() const
{
    return isActive;
}

void Device::setIsActive(bool value)
{
    isActive = value;
}

bool Device::getIsOn() const
{
    return isOn;
}

void Device::setIsOn(const bool &value)
{
    isOn = value;
}

unsigned int Device::getErrorCode() const
{
    return errorCode;
}

void Device::setErrorCode(const unsigned int &value)
{
    errorCode = value;
}

/*void Device::run()
{
    if(isActive)
    {
       changeDeviceStatus();
       std::string stringToControllerConnector = createArgument();
       ControllerConnector &instance = ControllerConnector::Instance();
       instance.setBuffer(stringToControllerConnector);
       ready();
    }
}*/

void Device::turnOn()
{
    if(isActive)
    {
        if(!isOn)
        {
            isOn = true;
            sendToControllerConnector();
        }
    }
}

void Device::turnOff()
{
    if(isActive)
    {
        if(isOn)
        {
            isOn = false;
            sendToControllerConnector();
        }
    }
}

void Device::sendToControllerConnector()
{
    std::vector<unsigned int> stringToControllerConnector = createArgument();
    ControllerConnector &instance = ControllerConnector::Instance();
    instance.pushBackToBuffer(stringToControllerConnector);
    ready();
}

std::vector<unsigned int> Device::createArgument()
{
    std::vector<unsigned int> argument =
    {
        output,
        errorCode,
        isOn,
        pause
    };
    return argument;
}

/*void Device::changeDeviceStatus()
{
    if(isOn)
    {
        isOn = false;
    }
    else
    {
        isOn = true;
    }
}*/
void Device::ready(){}

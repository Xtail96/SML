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

int Device::getErrorCode() const
{
    return errorCode;
}

void Device::setErrorCode(int value)
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
    std::string stringToControllerConnector = createArgument();
    ControllerConnector &instance = ControllerConnector::Instance();
    instance.setBuffer(stringToControllerConnector);
    ready();
}

std::string Device::createArgument()
{
    return std::string(std::to_string(output) + std::to_string(errorCode) + std::to_string(isOn) + std::to_string(pause));
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

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
            std::vector<unsigned int> argument = createArgument(1);
            sendToControllerConnector(argument);
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
            std::vector<unsigned int> argument =createArgument(0);
            sendToControllerConnector(argument);
        }
    }
}

void Device::sendToControllerConnector(const std::vector<unsigned int> &argument)
{

}

std::vector<unsigned int> Device::createArgument(const unsigned int &action)
{
    std::vector<unsigned int> argument;
    switch (action) {
    case 0: // turn off
    {
        argument =
        {
            output,
            errorCode,
            isOn,
            0,
            0,
            pause
        };
        break;
    }
    case 1: // turn on
    {
        argument =
        {
            output,
            errorCode,
            isOn,
            1,
            0,
            pause
        };
        break;
    }
    case 2: //update
    {
        argument =
        {
            output,
            errorCode,
            isOn,
            1,
            0,
            pause
        };
        break;
    }
    default:
        throw std::invalid_argument("Unknown action");
        break;
    }

    return argument;
}

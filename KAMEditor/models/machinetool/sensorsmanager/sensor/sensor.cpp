#include "sensor.h"
bool Sensor::getIsEnable() const
{
    return isEnable;
}

void Sensor::setIsEnable(bool value)
{
    if(isEnable != value)
    {
        isEnable = value;
    }
}

unsigned int Sensor::getPortNumber() const
{
    return portNumber;
}

unsigned int Sensor::getInputNumber() const
{
    return inputNumber;
}

std::string Sensor::getName() const
{
    return name;
}

Sensor::Sensor(std::string _name, unsigned int _portNumber, unsigned int _inputNumber, bool _isEnable) :
    name(_name), portNumber(_portNumber), inputNumber(_inputNumber), isEnable(_isEnable)
{

}


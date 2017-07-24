#include "sensor.h"
bool Sensor::getIsEnable() const
{
    return isEnable;
}

void Sensor::setIsEnable(bool value)
{
    isEnable = value;
}

Sensor::Sensor(std::string _name, unsigned int _inputNumber, bool _isEnable) :
    name(_name), inputNumber(_inputNumber), isEnable(_isEnable)
{

}


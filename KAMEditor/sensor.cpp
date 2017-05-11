#include "sensor.h"
Sensor::Sensor(unsigned int _id, std::string _name, bool _isEnabled) :
    id(_id), name(_name), isEnabled(_isEnabled), isActive(false), isStateChanged(false), isDebugActive(false)
{

}

bool Sensor::getIsActive() const
{
    return isActive;
}

void Sensor::setIsActive(bool value)
{
    isActive = value;
}

bool Sensor::getIsStateChanged() const
{
    return isStateChanged;
}

void Sensor::setIsStateChanged(bool value)
{
    isStateChanged = value;
}

std::string Sensor::getName() const
{
    return name;
}

void Sensor::setName(const std::string &value)
{
    name = value;
}

unsigned int Sensor::getId() const
{
    return id;
}

void Sensor::setId(unsigned int value)
{
    id = value;
}

void Sensor::setBuffer(const bool &value)
{
    buffer = value;
}

bool Sensor::getIsEnabled() const
{
    return isEnabled;
}

void Sensor::setIsEnabled(bool value)
{
    isEnabled = value;
}

bool Sensor::update()
{
    if(isEnabled)
    {
        if(isActive == buffer)
        {
            isStateChanged = false;
        }
        else
        {
            isActive = buffer;
            isStateChanged = true;
        }

        return isStateChanged;
    }
    else
    {
        return 0;
    }
}

#include "sensor.h"
Sensor::Sensor(unsigned int _id, std::string _name, bool _isEnabled) :
    input(_id), name(_name), isEnabled(_isEnabled), isOn(false), isStateChanged(false), isDebugActive(false)
{

}

void Sensor::update()
{
    /*if(isEnabled)
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
    }*/
}

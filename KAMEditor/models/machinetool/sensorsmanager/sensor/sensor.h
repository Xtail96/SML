#ifndef SENSOR_H
#define SENSOR_H

#include <string>

#include "models/structs.h"
class Sensor
{
private:
    std::string name;
    unsigned int portNumber;
    unsigned int inputNumber;
    bool isEnable;
public:
    Sensor(std::string _name, unsigned int _portNumber, unsigned int _inputNumber, bool _isEnable = false);
    bool getIsEnable() const;
    void setIsEnable(bool value);
    unsigned int getPortNumber() const;
    unsigned int getInputNumber() const;
    std::string getName() const;
};

#endif // SENSOR_H

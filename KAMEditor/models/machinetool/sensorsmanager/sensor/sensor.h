#ifndef SENSOR_H
#define SENSOR_H
#include <string>
class Sensor
{
private:
    std::string name;
    unsigned int inputNumber;
    bool isEnable;
public:
    Sensor(std::string _name, unsigned int _inputNumber, bool _isEnable = false);
    bool getIsEnable() const;
    void setIsEnable(bool value);
};

#endif // SENSOR_H

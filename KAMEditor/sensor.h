#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <QSensor>
#include <QPressureSensor>

#include "controllerconnector.h"

class Sensor
{
protected:
    unsigned int input;
    std::string name;
    bool isOn;
    bool isStateChanged;

    bool isEnabled;
    bool isDebugActive;

    bool buffer;
public:
    Sensor(unsigned int _id, std::string _name, bool _isEnabled);
    //! Методы получения и установки значений
private slots:
    void update();
};

#endif // SENSOR_H

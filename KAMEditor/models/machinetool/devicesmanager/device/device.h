#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

class Device
{
    bool isOn;
    unsigned int outputNumber;
public:
    Device(unsigned int _outputNumber, bool _isOn = false);
};

#endif // DEVICE_H

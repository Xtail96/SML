#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

#include "models/machinetool/settingsmanager/settingsmanager.h"

class Device
{
    std::string name;

    std::string boardName;

    unsigned int portNumber;

    unsigned int outputNumber;

    bool activeState;

    bool currentState;
public:
    Device(std::string _name);

    void setup(SettingsManager settingsManager);

    bool isEnable();

    std::string getBoardName() const;
    void setBoardName(const std::string &value);
    unsigned int getPortNumber() const;
    void setPortNumber(unsigned int value);
    unsigned int getOutputNumber() const;
    void setOutputNumber(unsigned int value);
    std::string getName() const;
    void setName(const std::string &value);
    bool getActiveState() const;
    void setActiveState(bool value);
    bool getCurrentState() const;
    void setCurrentState(bool value);
};

#endif // DEVICE_H

#ifndef DEVICE_H
#define DEVICE_H
#include <string>

#include <QMainWindow>

#include "models/machinetool/settingsmanager/settingsmanager.h"
#include "models/structs.h"

class Device
{
    std::string name;

    std::string boardName;

    unsigned int portNumber;

    unsigned int outputNumber;

    bool activeState;

    bool currentState;

    bool needToDisplay;

    byte mask;
public:
    Device(std::string _name, std::string _boardName = "undefined", unsigned int _portNumber = 0, unsigned int _outputNumber = 0, bool _activeState = false, bool _currentState = true, bool _needToDisplay = true, byte _mask = 0xff);

    void setup(const SettingsManager &settingsManager);

    bool isEnable() const;

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
    bool getNeedToDisplay() const;
    void setNeedToDisplay(bool value);
    byte getMask() const;
    void setMask(const byte &value);
};

#endif // DEVICE_H

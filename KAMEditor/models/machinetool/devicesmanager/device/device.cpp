#include "device.h"

QString Device::getBoardName() const
{
    return boardName;
}

void Device::setBoardName(const QString &value)
{
    boardName = value;
}

unsigned int Device::getPortNumber() const
{
    return portNumber;
}

void Device::setPortNumber(unsigned int value)
{
    portNumber = value;
}

unsigned int Device::getOutputNumber() const
{
    return outputNumber;
}

void Device::setOutputNumber(unsigned int value)
{
    outputNumber = value;
}

QString Device::getName() const
{
    return name;
}

void Device::setName(const QString &value)
{
    name = value;
}

bool Device::getActiveState() const
{
    return activeState;
}

void Device::setActiveState(bool value)
{
    activeState = value;
}

bool Device::getCurrentState() const
{
    return currentState;
}

void Device::setCurrentState(bool value)
{
    if(currentState != value)
    {
        currentState = value;
    }
}

bool Device::getNeedToDisplay() const
{
    return needToDisplay;
}

void Device::setNeedToDisplay(bool value)
{
    needToDisplay = value;
}

byte Device::getMask() const
{
    return mask;
}

void Device::setMask(const byte &value)
{
    mask = value;
}

QString Device::getCode() const
{
    return code;
}

Device::Device(QString _code,
               QString _name,
               QString _boardName,
               unsigned int _portNumber,
               unsigned int _outputNumber,
               bool _activeState,
               bool _currentState,
               bool _needToDisplay,
               byte _mask) :
    code(_code),
    name(_name),
    boardName(_boardName),
    portNumber(_portNumber),
    outputNumber(_outputNumber),
    activeState(_activeState),
    currentState(_currentState),
    needToDisplay(_needToDisplay),
    mask(_mask)
{
    setup();
}

void Device::setup()
{
    SettingsManager settingsManager;
    boardName = QVariant(settingsManager.get(code, "BoardName")).toString();
    portNumber = QVariant(settingsManager.get(code, "PortNumber")).toUInt();
    outputNumber = QVariant(settingsManager.get(code, "OutputNumber")).toUInt();
    activeState = QVariant(settingsManager.get(code, "ActiveState")).toBool();
    needToDisplay = QVariant(settingsManager.get(code, "NeedToDisplay")).toBool();
    mask = QVariant(settingsManager.get(code, "Mask")).toUInt();
    currentState = !activeState;
}

bool Device::isEnable() const
{
    return (activeState == currentState);
}

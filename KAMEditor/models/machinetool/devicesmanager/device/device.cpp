#include "device.h"

std::string Device::getBoardName() const
{
    return boardName;
}

void Device::setBoardName(const std::string &value)
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

std::string Device::getName() const
{
    return name;
}

void Device::setName(const std::string &value)
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

Device::Device(std::string _name, std::string _boardName, unsigned int _portNumber, unsigned int _outputNumber, bool _activeState, bool _currentState, bool _needToDisplay) :
    name(_name),
    boardName(_boardName),
    portNumber(_portNumber),
    outputNumber(_outputNumber),
    activeState(_activeState),
    currentState(_currentState),
    needToDisplay(_needToDisplay)
{

}

void Device::setup(SettingsManager settingsManager)
{
    QString qName = QString::fromStdString(name);
    boardName = QVariant(settingsManager.get(qName, "boardName")).toString().toStdString();
    portNumber = QVariant(settingsManager.get(qName, "portNumber")).toUInt();
    outputNumber = QVariant(settingsManager.get(qName, "outputNumber")).toUInt();
    activeState = QVariant(settingsManager.get(qName, "activeState")).toBool();
    needToDisplay = QVariant(settingsManager.get(qName, "needToDisplay")).toBool();
    currentState = !activeState;
}

bool Device::isEnable() const
{
    return (activeState == currentState);
}

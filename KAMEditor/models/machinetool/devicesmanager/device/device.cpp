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

Device::Device(std::string _name) :
    name(_name), boardName("undefined"), portNumber(0), outputNumber(0), activeState(false), currentState(true)
{

}

void Device::setup(SettingsManager settingsManager)
{
    QString qName = QString::fromStdString(name);
    boardName = QVariant(settingsManager.get(qName, "boardName")).toString().toStdString();
    portNumber = QVariant(settingsManager.get(qName, "portNumber")).toUInt();
    outputNumber = QVariant(settingsManager.get(qName, "outputNumber")).toUInt();
    activeState = QVariant(settingsManager.get(qName, "activeState")).toBool();
    currentState = !activeState;
}

bool Device::isEnable()
{
    return (activeState == currentState);
}

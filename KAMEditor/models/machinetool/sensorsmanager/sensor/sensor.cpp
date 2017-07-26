#include "sensor.h"
bool Sensor::getIsEnable() const
{
    return isEnable;
}

void Sensor::setIsEnable(bool value)
{
    if(isEnable != value)
    {
        isEnable = value;
    }
}

unsigned int Sensor::getPortNumber() const
{
    return portNumber;
}

unsigned int Sensor::getInputNumber() const
{
    return inputNumber;
}

std::string Sensor::getName() const
{
    return name;
}

std::string Sensor::getBoardName() const
{
    return boardName;
}

bool Sensor::getActiveState() const
{
    return activeState;
}


Sensor::Sensor(std::string _name, std::string _boardName, unsigned int _portNumber, unsigned int _inputNumber, bool _activeState, bool _isEnable, QColor _color) :
    name(_name), boardName(_boardName), portNumber(_portNumber), inputNumber(_inputNumber), activeState(_activeState), isEnable(_isEnable), color(_color)
{

}

QColor Sensor::getColor() const
{
    return color;
}

Sensor::Sensor(std::string _name) :
    name(_name), boardName("undefined"),portNumber(0), inputNumber(0), activeState(false), isEnable(false), color(QColor(0, 125, 0))
{

}

void Sensor::setup(SettingsManager settingsManager)
{
    portNumber = QVariant(settingsManager.get(QString::fromStdString(name), "portNumber")).toUInt();
    inputNumber = QVariant(settingsManager.get(QString::fromStdString(name), "inputNumber")).toUInt();
    boardName = QVariant(settingsManager.get(QString::fromStdString(name), "boardName")).toString().toStdString();
    activeState = QVariant(settingsManager.get(QString::fromStdString(name), "activeState")).toBool();
    color = QColor(QVariant(settingsManager.get(QString::fromStdString(name), "color")).toString());
    isEnable = false;
}

bool Sensor::isActive()
{
    return (isEnable == activeState);
}

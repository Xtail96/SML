#include "sensor.h"
bool Sensor::getCurrentState() const
{
    return currentState;
}

void Sensor::setCurrentState(bool value)
{
    if(currentState != value)
    {
        currentState = value;
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


Sensor::Sensor(std::string _name, std::string _boardName, unsigned int _portNumber, unsigned int _inputNumber, bool _activeState, bool _currentState, QColor _color) :
    name(_name), boardName(_boardName), portNumber(_portNumber), inputNumber(_inputNumber), activeState(_activeState), currentState(_currentState), color(_color)
{

}

QColor Sensor::getColor() const
{
    return color;
}

Sensor::Sensor(std::string _name) :
    name(_name), boardName("undefined"),portNumber(0), inputNumber(0), activeState(false), currentState(true), color(QColor(0, 125, 0))
{

}

void Sensor::setup()
{
    SettingsManager settingsManager;
    portNumber = QVariant(settingsManager.get(QString::fromStdString(name), "portNumber")).toUInt();
    inputNumber = QVariant(settingsManager.get(QString::fromStdString(name), "inputNumber")).toUInt();
    boardName = QVariant(settingsManager.get(QString::fromStdString(name), "boardName")).toString().toStdString();
    activeState = QVariant(settingsManager.get(QString::fromStdString(name), "activeState")).toBool();
    color = QColor(QVariant(settingsManager.get(QString::fromStdString(name), "color")).toString());
    currentState = !activeState;
}

bool Sensor::isActive()
{
    return (activeState == currentState);
}

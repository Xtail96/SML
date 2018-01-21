#include "sensor.h"

Sensor::Sensor(QString _code,
               QString _name,
               QString _boardName,
               unsigned int _portNumber,
               unsigned int _inputNumber,
               bool _activeState,
               bool _currentState,
               QColor _color) :
    code(_code),
    name(_name),
    boardName(_boardName),
    portNumber(_portNumber),
    inputNumber(_inputNumber),
    activeState(_activeState),
    currentState(_currentState),
    color(_color)
{
    setup();
}

void Sensor::setup()
{
    SettingsManager settingsManager;
    name = QVariant(settingsManager.get(code, "Label")).toString();
    portNumber = QVariant(settingsManager.get(code, "PortNumber")).toUInt();
    inputNumber = QVariant(settingsManager.get(code, "InputNumber")).toUInt();
    boardName = QVariant(settingsManager.get(code, "BoardName")).toString();
    activeState = QVariant(settingsManager.get(code, "ActiveState")).toBool();
    color = QColor(QVariant(settingsManager.get(code, "Color")).toString());
    currentState = !activeState;
}

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

QString Sensor::getName() const
{
    return name;
}

QString Sensor::getBoardName() const
{
    return boardName;
}

bool Sensor::getActiveState() const
{
    return activeState;
}


QString Sensor::getCode() const
{
    return code;
}

QColor Sensor::getColor() const
{
    return color;
}

bool Sensor::isActive()
{
    return (activeState == currentState);
}

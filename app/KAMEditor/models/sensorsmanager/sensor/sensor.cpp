#include "sensor.h"

Sensor::Sensor(QString _code,
               QString _name,
               QString _boardName,
               unsigned int _portNumber,
               unsigned int _inputNumber,
               bool _activeState,
               QColor _color) :
    code(_code),
    name(_name),
    boardName(_boardName),
    portNumber(_portNumber),
    inputNumber(_inputNumber),
    activeState(_activeState),
    currentState(!activeState),
    color(_color)
{
}

Sensor::Sensor(QString _code, SettingsManager *sm) :
    code(_code)
{
    if(sm == nullptr)
    {
        qDebug() << "new SettingsManager instance in sensor #" + code;
        sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
    else
    {
        setup(sm);
    }
}

void Sensor::setup(SettingsManager *sm)
{
    try
    {
        name = QVariant(sm->get(code, "Label")).toString();
        portNumber = QVariant(sm->get(code, "PortNumber")).toUInt();
        inputNumber = QVariant(sm->get(code, "InputNumber")).toUInt();
        boardName = QVariant(sm->get(code, "BoardName")).toString();
        activeState = QVariant(sm->get(code, "ActiveState")).toBool();
        color = QColor(QVariant(sm->get(code, "Color")).toString());
        currentState = !activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки датчика " + code, e.what()).exec();
    }
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

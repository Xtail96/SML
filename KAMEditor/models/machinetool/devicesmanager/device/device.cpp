#include "device.h"

Device::Device(QString _code,
               QString _name,
               QString _boardName,
               unsigned int _portNumber,
               unsigned int _outputNumber,
               bool _activeState,
               bool _needToDisplay,
               byte _mask) :
    code(_code),
    name(_name),
    boardName(_boardName),
    portNumber(_portNumber),
    outputNumber(_outputNumber),
    activeState(_activeState),
    currentState(!activeState),
    needToDisplay(_needToDisplay),
    mask(_mask)
{
}

Device::Device(QString _code, SettingsManager *sm) :
    code(_code)
{
    if(sm == nullptr)
    {
        qDebug() << "new SettingsManager instance in device #" + code;
        sm = new SettingsManager();
        setup(sm);
        delete sm;
    }
    else
    {
        setup(sm);
    }
}

void Device::setup(SettingsManager *sm)
{
    try
    {
        name = QVariant(sm->get(code, "Label")).toString();
        boardName = QVariant(sm->get(code, "BoardName")).toString();
        portNumber = QVariant(sm->get(code, "PortNumber")).toUInt();
        outputNumber = QVariant(sm->get(code, "OutputNumber")).toUInt();
        activeState = QVariant(sm->get(code, "ActiveState")).toBool();
        needToDisplay = QVariant(sm->get(code, "NeedToDisplay")).toBool();
        mask = QVariant(sm->get(code, "Mask")).toUInt();
        currentState = !activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + code, e.what()).exec();
    }
}

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

bool Device::isEnable() const
{
    return (activeState == currentState);
}

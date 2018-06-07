#include "device.h"

Device::Device(QString code,
               QString name,
               QString boardName,
               unsigned int portNumber,
               unsigned int outputNumber,
               bool activeState,
               bool needToDisplay,
               byte mask) :
    m_code(code),
    m_name(name),
    m_boardName(boardName),
    m_portNumber(portNumber),
    m_outputNumber(outputNumber),
    m_activeState(activeState),
    m_currentState(!m_activeState),
    m_needToDisplay(needToDisplay),
    m_mask(mask)
{
}

Device::Device(QString code, const SettingsManager &sm) :
    m_code(code)
{
    initialize(sm);
}

Device::~Device()
{

}

void Device::initialize(const SettingsManager &sm)
{
    try
    {
        m_name = QVariant(sm.get(m_code, "Label")).toString();
        m_boardName = QVariant(sm.get(m_code, "BoardName")).toString();
        m_portNumber = QVariant(sm.get(m_code, "PortNumber")).toUInt();
        m_outputNumber = QVariant(sm.get(m_code, "OutputNumber")).toUInt();
        m_activeState = QVariant(sm.get(m_code, "ActiveState")).toBool();
        m_needToDisplay = QVariant(sm.get(m_code, "NeedToDisplay")).toBool();
        m_mask = QVariant(sm.get(m_code, "Mask")).toUInt();
        m_currentState = !m_activeState;
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка настройки устройства " + m_code, e.what()).exec();
    }
}

QString Device::getBoardName() const
{
    return m_boardName;
}

void Device::setBoardName(const QString &value)
{
    m_boardName = value;
}

unsigned int Device::getPortNumber() const
{
    return m_portNumber;
}

void Device::setPortNumber(unsigned int value)
{
    m_portNumber = value;
}

unsigned int Device::getOutputNumber() const
{
    return m_outputNumber;
}

void Device::setOutputNumber(unsigned int value)
{
    m_outputNumber = value;
}

QString Device::getName() const
{
    return m_name;
}

void Device::setName(const QString &value)
{
    m_name = value;
}

bool Device::getActiveState() const
{
    return m_activeState;
}

void Device::setActiveState(bool value)
{
    m_activeState = value;
}

bool Device::getCurrentState() const
{
    return m_currentState;
}

void Device::setCurrentState(bool value)
{
    if(m_currentState != value)
    {
        m_currentState = value;
    }
}

bool Device::getNeedToDisplay() const
{
    return m_needToDisplay;
}

void Device::setNeedToDisplay(bool value)
{
    m_needToDisplay = value;
}

byte Device::getMask() const
{
    return m_mask;
}

void Device::setMask(const byte &value)
{
    m_mask = value;
}

QString Device::getCode() const
{
    return m_code;
}

bool Device::isEnable() const
{
    return (m_activeState == m_currentState);
}

#include "invalid_configuration_exception.h"

InvalidConfigurationException::InvalidConfigurationException(QString message) :
    m_message(message)
{

}

void InvalidConfigurationException::raise() const
{
    throw *this;
}

InvalidConfigurationException *InvalidConfigurationException::clone() const
{
    return new InvalidConfigurationException(*this);
}

QString InvalidConfigurationException::message() const
{
    return m_message;
}

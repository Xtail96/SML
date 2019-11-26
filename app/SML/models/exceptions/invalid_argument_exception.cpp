#include "invalid_argument_exception.h"

InvalidArgumentException::InvalidArgumentException(QString message) :
    m_message(message)
{

}

void InvalidArgumentException::raise() const
{
    throw *this;
}

InvalidArgumentException *InvalidArgumentException::clone() const
{
    return new InvalidArgumentException(*this);
}

QString InvalidArgumentException::message() const
{
    return m_message;
}

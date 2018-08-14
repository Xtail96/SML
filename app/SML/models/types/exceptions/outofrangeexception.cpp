#include "outofrangeexception.h"

OutOfRangeException::OutOfRangeException(QString message) :
    m_message(message)
{

}

void OutOfRangeException::raise() const
{
    throw *this;
}

OutOfRangeException *OutOfRangeException::clone() const
{
    return new OutOfRangeException(*this);
}

QString OutOfRangeException::message() const
{
    return m_message;
}

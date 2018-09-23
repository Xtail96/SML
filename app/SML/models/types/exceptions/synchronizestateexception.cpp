#include "synchronizestateexception.h"

SynchronizeStateException::SynchronizeStateException(QString message) :
    m_message(message)
{

}

void SynchronizeStateException::raise() const
{
    throw *this;
}

SynchronizeStateException *SynchronizeStateException::clone() const
{
    return new SynchronizeStateException(*this);
}

QString SynchronizeStateException::message() const
{
    return m_message;
}

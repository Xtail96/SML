#include "controllerconnector.h"

ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

ControllerConnector::ControllerConnector() :
    buffer("")
{

}

std::string ControllerConnector::getBuffer() const
{
    return buffer;
}

void ControllerConnector::setBuffer(const std::string &s)
{
    if(buffer == "")
    {
        buffer = s;
    }
    else
    {
        buffer += '|' + s;
    }
}

void ControllerConnector::clearBuffer()
{
    buffer = "";
}

void ControllerConnector::send()
{

}

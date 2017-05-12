#include "controllerconnector.h"

ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

ControllerConnector::ControllerConnector() :
    buffer(buffer = std::vector< std::vector<unsigned int> >(0))
{

}

void ControllerConnector::pushBackToBuffer(const std::vector<unsigned int> &element)
{
    buffer.push_back(element);
}

std::vector< std::vector<unsigned int> >ControllerConnector::getBuffer() const
{
    return buffer;
}

/*std::vector<unsigned int> ControllerConnector::readFromTheBuffer(const unsigned int &position)
{
    if(position < buffer.size())
    {
        return buffer[position];
    }
    else
    {
        throw std::invalid_argument("Buffer does not have this element");
    }
}*/

std::vector<unsigned int> ControllerConnector::readInputInformation(const unsigned int &inputNumber) const
{
    std::vector<unsigned int> inputInformation = std::vector<unsigned int>(0);
    for(auto element : buffer)
    {
        if(element[0] == inputNumber)
        {
            inputInformation = element;
            break;
        }
    }
    return inputInformation;
}

#include "controllerconnector.h"
ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

ControllerConnector::ControllerConnector() :
    buffer(std::vector< std::vector<unsigned int> >(0))
{

}

void ControllerConnector::pushBackToBuffer(const std::vector<unsigned int> &element)
{
    buffer.push_back(element);
}

void ControllerConnector::insertToDevicesMap(const unsigned int &deviceOutput, const DeviceBuffer &deviceBuffer)
{
    devicesMap.insert(std::make_pair(deviceOutput, deviceBuffer));
}

void ControllerConnector::updateDevicesMapElelment(const unsigned int &deviceOutput, const DeviceBuffer &deviceBuffer)
{
    for(auto it : devicesMap)
    {
        if(it.first == deviceOutput)
        {
            it.second = deviceBuffer;
        }
    }
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


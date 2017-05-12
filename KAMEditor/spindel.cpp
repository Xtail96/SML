#include "spindel.h"

Spindel::Spindel(unsigned int _output, std::string _spindle_name, unsigned int _minJog, unsigned int maxJog, bool _isReady) :
    Device(_output, _spindle_name),
    currentJog(0),
    jogLimits(std::make_pair(_minJog, maxJog)),
    isReady(_isReady)
{

}

unsigned int Spindel::getJog() const
{
    return currentJog;
}

void Spindel::setJog(unsigned int value)
{
    currentJog = value;
}

std::pair<unsigned int, unsigned int> Spindel::getJogLimits() const
{
    return jogLimits;
}

void Spindel::setJogLimits(const std::pair<unsigned int, unsigned int> &value)
{
    jogLimits = value;
}

bool Spindel::getIsReady() const
{
    return isReady;
}

void Spindel::setIsReady(bool value)
{
    isReady = value;
}

/*void Spindel::run()
{
    if(isActive)
    {
       std::string stringToControllerConnector = createArgument();
       ControllerConnector &instance = ControllerConnector::Instance();
       instance.setBuffer(stringToControllerConnector);
       ready();
    }
}*/

void Spindel::calibrateSpindelJog(unsigned int jog)
{
    if(isActive)
    {
        currentJog = jog;
    }
}

std::string Spindel::createArgument()
{
    return std::string(std::to_string(output) + std::to_string(isOn) + std::to_string(errorCode) + std::to_string(currentJog));
}


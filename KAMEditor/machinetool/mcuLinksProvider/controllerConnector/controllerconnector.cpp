#include "controllerconnector.h"
ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

ControllerConnector::ControllerConnector()
{

}

ControllerConnector::~ControllerConnector()
{

}

void ControllerConnector::send()
{

}

void ControllerConnector::recieved()
{

}

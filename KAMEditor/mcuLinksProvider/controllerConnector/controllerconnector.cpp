#include "controllerconnector.h"
ControllerConnector& ControllerConnector::Instance()
{
    static ControllerConnector m;
    return m;
}

void ControllerConnector::send()
{

}

ControllerConnector::ControllerConnector()
{

}

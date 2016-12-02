#include "commandinterpreter.h"


CommandInterpreter& CommandInterpreter::Instance()
{
    static CommandInterpreter m;
    return m;
}


void CommandInterpreter::addPoint(Point p)
{
    points.push_back(p);
}

void CommandInterpreter::setPoint(unsigned int num, Point p)
{
    if (num < points.size())
        points[num] = p;
}


void CommandInterpreter::removePoint(unsigned int num)
{
    if (num < points.size())
        points.erase(points.begin() + num);
}


std::vector<Point> CommandInterpreter::getPoints()
{
    return points;
}


bool CommandInterpreter::setSelectedPoint(unsigned int num)
{
    if(num < points.size())
    {
        selectedPoint = num;
        return true;
    }
    else
    {
        return false;
    }
}


unsigned int CommandInterpreter::getSelectedPoint()
{
    return selectedPoint;
}

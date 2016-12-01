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
void CommandInterpreter::setPointToSelect(unsigned int num)
{
    point_to_select = num;
}
unsigned int CommandInterpreter::getPointToSelect()
{
    return point_to_select;
}

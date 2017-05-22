#include "pointsmanager.h"


PointsManager& PointsManager::Instance()
{
    static PointsManager m;
    return m;
}


void PointsManager::addPoint(Point p)
{
    points.push_back(p);
}

void PointsManager::setPoint(unsigned int num, Point p)
{
    if (num < points.size())
        points[num] = p;
}


void PointsManager::removePoint(unsigned int num)
{
    if (num < points.size())
        points.erase(points.begin() + num);
}


std::vector<Point> PointsManager::getPoints()
{
    return points;
}


bool PointsManager::setSelectedPoint(unsigned int num)
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


unsigned int PointsManager::getSelectedPoint()
{
    return selectedPoint;
}

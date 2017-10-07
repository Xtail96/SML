#include "pointsbuilder.h"

PointsBuilder::PointsBuilder()
{

}

Point *PointsBuilder::buildPoint(QStringList coordinatesStringList)
{
    Point* point;
    std::vector<double> coordinates;
    for(auto coordinateString : coordinatesStringList)
    {
        coordinates.push_back(coordinateString.toDouble());
    }
    point = new Point(coordinates);
    return point;
}

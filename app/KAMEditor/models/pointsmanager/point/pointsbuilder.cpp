#include "pointsbuilder.h"

PointsBuilder::PointsBuilder()
{

}

/*Point *PointsBuilder::buildPoint(QStringList coordinatesStringList, size_t machineToolAxisesCount)
{
    Point* point;
    std::vector<double> coordinates;
    size_t coordinatesStringListSize = coordinatesStringList.size();

    if(machineToolAxisesCount == coordinatesStringListSize)
    {
        for(auto coordinateString : coordinatesStringList)
        {
            coordinates.push_back(coordinateString.toDouble());
        }
    }
    else
    {
        if(machineToolAxisesCount > coordinatesStringListSize)
        {
            size_t delta = machineToolAxisesCount - coordinatesStringListSize;
            for(auto coordinateString : coordinatesStringList)
            {
                coordinates.push_back(coordinateString.toDouble());
            }
            for(size_t i = 0; i < delta; i++)
            {
                coordinates.push_back(0);
            }
        }
        else
        {
            for(size_t i = 0; i < machineToolAxisesCount; i++)
            {
                coordinates.push_back(coordinatesStringList[i].toDouble());
            }
        }
    }

    point = new Point(coordinates);
    return point;
}*/

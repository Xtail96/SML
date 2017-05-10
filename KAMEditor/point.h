#ifndef POINT_H
#define POINT_H
#include <vector>

#include "structs.h"
#include "machinetool.h"

//typedef VectorDouble Point;

struct Point{
    std::vector<double> coordinates;

    Point()
    {
        MachineTool &instance = MachineTool::Instance();
        int axisCount = instance.getAxisCount();

        for(int i = 0; i < axisCount; i++)
        {
            coordinates.push_back(0);
        }
    }

    Point(std::vector<double> _coordinates)
    {
        coordinates = _coordinates;
    }

    std::vector<double> getCoordinates() const
    {
        return coordinates;
    }

    void setCoordinates(const std::vector<double> &value)
    {
        coordinates = value;
    }
};


#endif // POINT_H


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
        MachineTool &instance = MachineTool::Instance();
        unsigned int axisCount = instance.getAxisCount();
        if(axisCount == _coordinates.size())
        {
            coordinates = _coordinates;
        }
        else
        {
            if(axisCount > _coordinates.size())
            {
                unsigned int difference = axisCount - _coordinates.size();
                coordinates = _coordinates;
                for(unsigned int i = 0; i < difference; i++)
                {
                    coordinates.push_back(0);
                }
            }
            else
            {
                for(unsigned int i = 0; i < axisCount; i++)
                {
                    coordinates.push_back(_coordinates[i]);
                }
            }
        }
    }

    std::vector<double> getCoordinates() const
    {
        return coordinates;
    }

    void setCoordinates(const std::vector<double> &value)
    {
        coordinates = value;
    }

    double operator[](std::string s)
    {
        unsigned int i = axisNames.getValueByName(s);
        return coordinates[i];
    }
};


#endif // POINT_H


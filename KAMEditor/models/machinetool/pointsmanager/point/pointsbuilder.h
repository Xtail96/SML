#ifndef POINTSBUILDER_H
#define POINTSBUILDER_H

#include "models/machinetool/pointsmanager/point/point.h"

class PointsBuilder
{
public:
    PointsBuilder();

    static Point* buildPoint(QStringList coordinatesStringList);
};

#endif // POINTSBUILDER_H

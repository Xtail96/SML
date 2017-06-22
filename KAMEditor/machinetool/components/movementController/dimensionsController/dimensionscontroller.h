#ifndef DIMENSIONSCONTROLLER_H
#define DIMENSIONSCONTROLLER_H
#include "machinetool/components/pointsManager/point/point.h"

class DimensionsController
{
private:

public:
    DimensionsController();
    bool isMovementCorrect(const Point &axisesLength, const Point &newCoordinates);
};

#endif // DIMENSIONSCONTROLLER_H

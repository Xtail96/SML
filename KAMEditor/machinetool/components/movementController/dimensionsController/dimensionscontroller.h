#ifndef DIMENSIONSCONTROLLER_H
#define DIMENSIONSCONTROLLER_H
#include "machinetool/components/pointsManager/point/point.h"

class DimensionsController
{
private:
    bool isDimensionControlEnable;
public:
    DimensionsController(bool _isDimensionControlEnable = false);
    bool isMovementCorrect(const Point &axisesLength, const Point &newCoordinates);
    bool getIsDimensionControlEnable() const;
    void setIsDimensionControlEnable(bool value);
};

#endif // DIMENSIONSCONTROLLER_H

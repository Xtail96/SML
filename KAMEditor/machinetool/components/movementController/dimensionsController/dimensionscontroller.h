#ifndef DIMENSIONSCONTROLLER_H
#define DIMENSIONSCONTROLLER_H
#include "machinetool/components/pointsManager/point/point.h"

class DimensionsController
{
private:
    int axisesCount;
    bool isDimensionControlEnable;
public:
    DimensionsController(int _axisesCount, bool _isDimensionControlEnable = false);
    bool isMovementCorrect(Point &axisesLength, Point &newCoordinates);
    bool checkAxisesCoordinates(Point &axisesLength, Point &newCoordinates);

    bool getIsDimensionControlEnable() const;
    void setIsDimensionControlEnable(bool value);
};

#endif // DIMENSIONSCONTROLLER_H

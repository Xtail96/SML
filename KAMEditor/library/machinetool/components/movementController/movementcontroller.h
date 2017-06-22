#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H
#include "machinetool/structs.h"
#include "machinetool/components/movementController/dimensionsController/dimensionscontroller.h"
#include "machinetool/components/pointsManager/point/point.h"

class MovementController
{
private:
    Point currentCoordinates;
    Point currentCoordinatesFromBase;
    Point parkCoordinates;
    // шаг движения
    double step;
    double velocity;
    DimensionsController dimensionsController;
public:
    MovementController();
    virtual void stepMove(const Point &to);
    virtual void move(const Point &offset);
    void checkCurrentCoordinates();
};

#endif // MOVEMENTCONTROLLER_H

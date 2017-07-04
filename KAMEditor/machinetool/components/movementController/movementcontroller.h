#ifndef MOVEMENTCONTROLLER_H
#define MOVEMENTCONTROLLER_H
#include "machinetool/structs.h"
#include "machinetool/components/movementController/axises/axis.h"
#include "machinetool/components/pointsManager/point/point.h"
#include "machinetool/components/movementController/dimensionsController/dimensionscontroller.h"

class MovementController
{
private:
    /// Оси станка
    std::vector< std::shared_ptr<Axis> > axises;

    Point currentCoordinates;
    Point currentCoordinatesFromBase;
    Point parkCoordinates;
    Point axisesLength;
    // шаг движения
    double step;
    double velocity;
    DimensionsController dimensionsController;
public:
    MovementController(unsigned int _axisesCount, double _step = -1, double _velocity = 30);
    void addAxises(const unsigned int &count);
    void setupAxises();
    std::vector<std::shared_ptr<Axis> > getAxises() const;
    void setAxises(const std::vector<std::shared_ptr<Axis> > &value);
    virtual void stepMove(Point &to);
    virtual void move(const Point &offset);
    bool checkCurrentCoordinates(Point &newCoordinates);
    Point getAxisesLength();
};

#endif // MOVEMENTCONTROLLER_H

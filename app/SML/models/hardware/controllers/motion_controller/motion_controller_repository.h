#ifndef MOTIONCONTROLLERREPOSITORY_H
#define MOTIONCONTROLLERREPOSITORY_H

#include "./axis/axis.h"

class MotionControllerRepository
{
public:
    MotionControllerRepository();
    ~MotionControllerRepository();

    bool axisExists(AxisId id);
    Axis &axis(AxisId id);
    void setAxisValue(AxisId id, double value);
    QList<Axis> axes();

private:
    /// Доступные оси станка.
    QList<Axis> m_axes;

    void addAxis(AxisId id, double initialPosition);
    void removeAxis(AxisId id);
    void clearAxes();

    friend class MotionController;
};

#endif // MOTIONCONTROLLERREPOSITORY_H

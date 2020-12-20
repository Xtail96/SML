#ifndef MOTIONCONTROLLERREPOSITORY_H
#define MOTIONCONTROLLERREPOSITORY_H

#include "./axis.h"

class MotionControllerRepository
{
public:
    MotionControllerRepository();
    ~MotionControllerRepository();

    bool axisExists(Axis::Id id);
    Axis::State &axis(Axis::Id id);
    void setAxisValue(Axis::Id id, double value);
    QList<Axis::State> axes();

private:
    /// Доступные оси станка.
    QList<Axis::State> m_axes;

    void addAxis(Axis::Id id, double initialPosition);
    void removeAxis(Axis::Id id);
    void clearAxes();

    friend class MotionController;
};

#endif // MOTIONCONTROLLERREPOSITORY_H

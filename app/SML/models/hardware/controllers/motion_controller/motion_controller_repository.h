#ifndef MOTIONCONTROLLERREPOSITORY_H
#define MOTIONCONTROLLERREPOSITORY_H

#include "./axis_state.h"

class MotionControllerRepository
{
public:
    MotionControllerRepository();
    ~MotionControllerRepository();

    bool axisExists(AxisId id);
    AxisState &axis(AxisId id);
    void setAxisValue(AxisId id, double value);
    QList<AxisState> axes();

private:
    /// Доступные оси станка.
    QList<AxisState> m_axes;

    void addAxis(AxisId id, double initialPosition);
    void removeAxis(AxisId id);
    void clearAxes();

    friend class MotionController;
};

#endif // MOTIONCONTROLLERREPOSITORY_H

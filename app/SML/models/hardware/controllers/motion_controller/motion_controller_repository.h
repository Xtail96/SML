#ifndef MOTIONCONTROLLERREPOSITORY_H
#define MOTIONCONTROLLERREPOSITORY_H

#include "./axis/axis.h"

class MotionControllerRepository : public QObject
{
    Q_OBJECT
public:
    MotionControllerRepository(QObject *parent = nullptr);
    ~MotionControllerRepository();

    bool axisExists(AxisId id);
    Axis* axis(AxisId id);
    QList<Axis*> axes();

private:
    /// Доступные оси станка.
    QSet<Axis*> m_axes;

    void addAxis(AxisId id, double initialPosition);
    void removeAxis(AxisId id);
    void clearAxes();

    friend class MotionController;
};

#endif // MOTIONCONTROLLERREPOSITORY_H

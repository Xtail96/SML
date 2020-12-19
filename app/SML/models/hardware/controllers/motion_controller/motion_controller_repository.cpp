#include "motion_controller_repository.h"

MotionControllerRepository::MotionControllerRepository():
    m_axes()
{

}

MotionControllerRepository::~MotionControllerRepository()
{
}

bool MotionControllerRepository::axisExists(AxisId id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return true;
    }

    return false;
}

Axis& MotionControllerRepository::axis(AxisId id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return axis;
    }

    throw std::invalid_argument("unknown axis " + Axis::decorateId(id).toStdString());
}

void MotionControllerRepository::setAxisValue(AxisId id, double value)
{
    this->axis(id).setCurrentPosition(value);
}

QList<Axis> MotionControllerRepository::axes()
{
    QList<Axis> axes = m_axes;
    std::sort(axes.begin(), axes.end());
    return axes;
}

void MotionControllerRepository::addAxis(AxisId id, double initialPosition)
{
    if(this->axisExists(id))
    {
        qWarning() << "Axis" << Axis::decorateId(id) << "is already exists. Ignored.";
        return;
    }

    m_axes.append(Axis(id, initialPosition));
}

void MotionControllerRepository::removeAxis(AxisId id)
{
    m_axes.removeAll(this->axis(id));
}

void MotionControllerRepository::clearAxes()
{
    m_axes.clear();
}

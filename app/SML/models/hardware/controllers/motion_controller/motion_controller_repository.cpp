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

AxisState& MotionControllerRepository::axis(AxisId id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return axis;
    }

    throw std::invalid_argument("unknown axis " + AxisState::decorateId(id).toStdString());
}

void MotionControllerRepository::setAxisValue(AxisId id, double value)
{
    this->axis(id).setCurrentPosition(value);
}

QList<AxisState> MotionControllerRepository::axes()
{
    QList<AxisState> axes = m_axes;
    std::sort(axes.begin(), axes.end());
    return axes;
}

void MotionControllerRepository::addAxis(AxisId id, double initialPosition)
{
    if(this->axisExists(id))
    {
        qWarning() << "Axis" << AxisState::decorateId(id) << "is already exists. Ignored.";
        return;
    }

    m_axes.append(AxisState(id, initialPosition));
}

void MotionControllerRepository::removeAxis(AxisId id)
{
    m_axes.removeAll(this->axis(id));
}

void MotionControllerRepository::clearAxes()
{
    m_axes.clear();
}

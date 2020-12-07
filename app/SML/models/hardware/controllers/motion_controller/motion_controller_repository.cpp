#include "motion_controller_repository.h"

MotionControllerRepository::MotionControllerRepository(QObject *parent):
    QObject(parent),
    m_axes()
{

}

MotionControllerRepository::~MotionControllerRepository()
{
    qDeleteAll(m_axes.begin(), m_axes.end());
}

bool MotionControllerRepository::axisExists(AxisId id)
{
    for(auto axis : m_axes)
    {
       if(axis->id() == id)
           return true;
    }

    return false;
}

Axis *MotionControllerRepository::axis(AxisId id)
{
    for(auto axis : m_axes)
    {
       if(axis->id() == id)
           return axis;
    }

    throw std::invalid_argument("invalid axis id" + Axis::decorateId(id).toStdString());
}

QList<Axis *> MotionControllerRepository::axes()
{
    QList<Axis *> axes = m_axes.toList();
    auto axisPointerCmp = [=](Axis* a1, Axis* a2) { return *(a1) <= *(a2); };
    std::sort(axes.begin(), axes.end(), axisPointerCmp);
    return axes;
}

void MotionControllerRepository::addAxis(AxisId id, double initialPosition)
{
    m_axes.insert(new Axis(id, initialPosition, this));
}

void MotionControllerRepository::removeAxis(AxisId id)
{
    m_axes.remove(this->axis(id));
}

void MotionControllerRepository::clearAxes()
{
    m_axes.clear();
}

#include "axes_repository.h"

AxesRepository::AxesRepository():
    m_axes()
{

}

AxesRepository::~AxesRepository()
{
}

bool AxesRepository::axisExists(Axis::Id id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return true;
    }

    return false;
}

Axis::State& AxesRepository::axis(Axis::Id id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return axis;
    }

    throw std::invalid_argument("unknown axis " + Axis::decorateId(id).toStdString());
}

void AxesRepository::setAxisValue(Axis::Id id, double value)
{
    this->axis(id).setCurrentPosition(value);
}

QList<Axis::State> AxesRepository::axes()
{
    QList<Axis::State> axes = m_axes;
    std::sort(axes.begin(), axes.end());
    return axes;
}

void AxesRepository::addAxis(Axis::Id id, double initialPosition)
{
    if(this->axisExists(id))
    {
        qWarning() << "Axis" << Axis::decorateId(id) << "is already exists. Ignored.";
        return;
    }

    m_axes.append(Axis::State(id, initialPosition));
}

void AxesRepository::removeAxis(Axis::Id id)
{
    m_axes.removeAll(this->axis(id));
}

void AxesRepository::clearAxes()
{
    m_axes.clear();
}

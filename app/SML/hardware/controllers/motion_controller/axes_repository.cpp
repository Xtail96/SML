#include "axes_repository.h"

AxesRepository::AxesRepository():
    IRepository<Axis::Id, Axis::State>(),
    m_axes()
{

}

AxesRepository::~AxesRepository()
{
}

Axis::State AxesRepository::createAxis(Axis::Id id, double posFromBase)
{
    return Axis::State(id, posFromBase);
}

bool AxesRepository::exists(Axis::Id id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return true;
    }

    return false;
}

Axis::State& AxesRepository::get(Axis::Id id)
{
    for(auto& axis : m_axes)
    {
        if(axis.id() == id)
            return axis;
    }

    throw std::invalid_argument("unknown axis " + Axis::decorateId(id).toStdString());
}

QList<Axis::State> AxesRepository::getAll()
{
    QList<Axis::State> axes = m_axes;
    std::sort(axes.begin(), axes.end());
    return axes;
}

void AxesRepository::add(Axis::State value)
{
    if(this->exists(value.id()))
    {
        qWarning() << "Axis" << Axis::decorateId(value.id()) << "is already exists. Ignored.";
        return;
    }

    m_axes.append(value);
}

void AxesRepository::remove(Axis::Id id)
{
    m_axes.removeAll(this->get(id));
}

void AxesRepository::clear()
{
    m_axes.clear();
}

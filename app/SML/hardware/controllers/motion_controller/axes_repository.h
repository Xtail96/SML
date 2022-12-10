#ifndef AXESREPOSITORY_H
#define AXESREPOSITORY_H

#include "./axis.h"
#include "./common/interfaces/i_repository.h"

class AxesRepository: IRepository<Axis::Id, Axis::State>
{
public:
    AxesRepository();
    ~AxesRepository();
    bool exists(Axis::Id id) override;
    Axis::State& get(Axis::Id id) override;
    QList<Axis::State> getAll() override;
    void add(Axis::State value) override;
    void remove(Axis::Id id) override;
    void clear() override;
    static Axis::State createAxis(Axis::Id id, double posFromBase);
private:
    /// Доступные оси станка.
    QList<Axis::State> m_axes;
};

#endif // AXESREPOSITORY_H

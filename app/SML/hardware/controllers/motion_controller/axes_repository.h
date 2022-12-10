#ifndef AXESREPOSITORY_H
#define AXESREPOSITORY_H

#include "./axis.h"

template <typename ID, typename VAL>
class IRepository {
public:
    virtual bool exists(ID id) = 0;
    virtual VAL& get(ID id) = 0;
    virtual QList<VAL> getAll() = 0;
    virtual void remove(ID id) = 0;
    virtual void add(VAL value) = 0;
    virtual void clear() = 0;
};


class AxesRepository: IRepository<Axis::Id, Axis::State>
{
public:
    AxesRepository();
    ~AxesRepository();
    static Axis::State createAxis(Axis::Id id, double posFromBase);

    bool exists(Axis::Id id) override;
    Axis::State& get(Axis::Id id) override;
    QList<Axis::State> getAll() override;
    void add(Axis::State value) override;
    void remove(Axis::Id id) override;
    void clear() override;

private:
    /// Доступные оси станка.
    QList<Axis::State> m_axes;

    friend class MotionController;
};

#endif // MOTIONCONTROLLERREPOSITORY_H

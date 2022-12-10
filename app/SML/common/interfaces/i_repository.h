#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include <QList>

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

#endif // IREPOSITORY_H

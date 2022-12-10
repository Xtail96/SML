#ifndef SENSORSREPOSITORY_H
#define SENSORSREPOSITORY_H

#include "./common/interfaces/i_repository.h"
#include "./sensor.h"

class SensorsRepository : public IRepository<QString, Sensor>
{
public:
    SensorsRepository();
    ~SensorsRepository();
    bool exists(QString id) override;
    Sensor& get(QString id) override;
    QList<Sensor> getAll() override;
    void add(Sensor value) override;
    void remove(QString id) override;
    void clear() override;
private:
    QList<Sensor> m_sensors;
};

#endif // SENSORSREPOSITORY_H

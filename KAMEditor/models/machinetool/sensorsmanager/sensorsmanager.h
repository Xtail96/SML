#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

class SensorsManager
{
private:
    std::vector< std::shared_ptr<Sensor> > sensors;
public:
    SensorsManager();
    void initilize();
    std::vector<std::shared_ptr<Sensor> > getSensors() const;
};

#endif // SENSORSMANAGER_H

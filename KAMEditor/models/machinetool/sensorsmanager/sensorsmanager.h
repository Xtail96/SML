#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/machinetool/sensorsmanager/sensor/sensor.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

class SensorsManager
{
public:
    std::vector< std::shared_ptr<Sensor> > sensors;
    SensorsManager();
    void initilize();
};

#endif // SENSORSMANAGER_H

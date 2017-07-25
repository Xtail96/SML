#include "sensorsmanager.h"

SensorsManager::SensorsManager()
{
    Sensor* tmpX = new Sensor("XAxisSensor", 1, 0);
    Sensor* tmpY = new Sensor("YAxisSensor", 1, 1);
    Sensor* tmpZ = new Sensor("ZAxisSensor", 1, 2);

    sensors =
    {
        std::shared_ptr<Sensor>(tmpX),
        std::shared_ptr<Sensor>(tmpY),
        std::shared_ptr<Sensor>(tmpZ)
    };
}

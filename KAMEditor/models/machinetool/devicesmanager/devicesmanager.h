#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/machinetool/devicesmanager/device/device.h"

class DevicesManager
{
private:
    std::vector< std::shared_ptr<Device> > devices;
public:
    DevicesManager();

    std::vector<std::shared_ptr<Device> >& getDevices();

    void updateDevices(const std::vector<std::shared_ptr<Device> > &value);

    void initialize();
};

#endif // DEVICESMANAGER_H

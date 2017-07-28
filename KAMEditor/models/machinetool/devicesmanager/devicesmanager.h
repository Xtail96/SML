#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/machinetool/devicesmanager/device/device.h"
#include "models/structs.h"

class DevicesManager
{
private:
    std::vector< std::shared_ptr<Device> > devices;

    DevicesBuffer devicesBuffer;

public:
    DevicesManager();

    std::vector<std::shared_ptr<Device> >& getDevices();

    DevicesBuffer getDevicesBuffer() const;

    void updateDevices(const std::vector<std::shared_ptr<Device> > &value);

    void initialize();

    byte_array getSwitchDevicePackege(std::string deviceName, bool turnOn, byte firstAgrument = 0x00, byte secondArgument = 0x00);

    Device& findDevice(std::string deviceName);

    byte getSwitchKey(std::string boardName, unsigned int portNumber, unsigned int outputNumber);
};

#endif // DEVICESMANAGER_H

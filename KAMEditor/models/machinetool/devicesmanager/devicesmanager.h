#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/machinetool/devicesmanager/device/device.h"
#include "models/structs.h"

class DevicesManager
{
private:
    const unsigned char SET_DEVICES = 16;

    std::vector< std::shared_ptr<Device> > devices;

    DevicesBuffer devicesBuffer;

    byte getDeviceMask(std::string boardName, unsigned int portNumber, unsigned int outputNumber);
public:
    DevicesManager();

    std::vector<std::shared_ptr<Device> >& getDevices();

    DevicesBuffer getDevicesBuffer() const;

    void updateDevices(const std::vector<std::shared_ptr<Device> > &value);

    void initialize();

    byte_array getSwitchDeviceData(const Device &device, byte firstAgrument = 0x00, byte secondArgument = 0x00);

    Device& findDevice(std::string deviceName);
};

#endif // DEVICESMANAGER_H

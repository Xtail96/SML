#ifndef DEVICEREPOSITORY_H
#define DEVICEREPOSITORY_H

#include "./common/interfaces/i_repository.h"
#include "./device.h"

class DeviceRepository //: public IRepository<int, Device>
{
public:
    DeviceRepository();
    ~DeviceRepository();

private:
    QList<Device> m_devices;
};

#endif // DEVICEREPOSITORY_H

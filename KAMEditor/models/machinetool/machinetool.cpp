#include "machinetool.h"

MachineTool::MachineTool(uint16_t _vendorId, uint16_t _productId, const unsigned int _axisesCount) :
    vendorId(_vendorId), productId(_productId), movementController(_axisesCount)
{
}

MachineTool::~MachineTool()
{

}

MovementsHandler MachineTool::getMovementController() const
{
    return movementController;
}

std::vector<std::shared_ptr<Sensor> > MachineTool::getSensors() const
{
    return sensors;
}

void MachineTool::setSensors(const std::vector<std::shared_ptr<Sensor> > &value)
{
    sensors = value;
}

std::vector<std::shared_ptr<Device> > MachineTool::getDevices() const
{
    return devices;
}

void MachineTool::setDevices(const std::vector<std::shared_ptr<Device> > &value)
{
    devices = value;
}

uint16_t MachineTool::getVendorId() const
{
    return vendorId;
}

uint16_t MachineTool::getProductId() const
{
    return productId;
}

PointsManager& MachineTool::getPointsManager()
{
    return pointsManager;
}

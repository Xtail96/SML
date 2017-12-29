#include "usbdevicesmanager.h"

UsbDevicesManager::UsbDevicesManager(const MachineTool *machineTool)
{
    try
    {
        u1 = std::shared_ptr<UsbDevice>(new U1(machineTool->getVendorId(), machineTool->getProductId()));
    }
    catch(std::runtime_error e)
    {
        u1 = NULL;
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

std::shared_ptr<UsbDevice> UsbDevicesManager::getU1() const
{
    return u1;
}

UsbDevicesManager::~UsbDevicesManager()
{

}

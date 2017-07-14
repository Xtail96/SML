#include "usbdevicemanager.h"

UsbDeviceManager::UsbDeviceManager(const MachineTool *machineTool)
{
    try
    {
        u1 = std::shared_ptr<UsbDevice>(new UsbDevice(machineTool->getVendorId(), machineTool->getProductId()));
    }
    catch(std::runtime_error e)
    {
        u1 = NULL;
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

std::shared_ptr<UsbDevice> UsbDeviceManager::getU1() const
{
    return u1;
}

UsbDeviceManager::~UsbDeviceManager()
{

}

#include "usbxpressdevicemanager.h"

SiLabsU1 *UsbXpressDeviceManager::getU1() const
{
    return u1;
}

UsbXpressDeviceManager::UsbXpressDeviceManager(MachineTool *_machineTool) :
    machineTool(_machineTool)
{
    try
    {
        u1 = new SiLabsU1(machineTool);
    }
    catch(std::runtime_error e)
    {
        u1 = NULL;
        throw;
    }
}

UsbXpressDeviceManager::~UsbXpressDeviceManager()
{
    u1->free();
    delete u1;
    delete machineTool;
}

void UsbXpressDeviceManager::connectWithSiLabsDevice()
{
    try
    {
        u1->free();
        u1->initialize(machineTool->getName());
    }
    catch(std::runtime_error e)
    {
        u1 = nullptr;
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        throw;
    }
}

#include "usbxpressdevicemanager.h"
#ifdef Q_OS_WIN

SiLabsU1 *UsbXpressDeviceManager::getU1() const
{
    return u1;
}

UsbXpressDeviceManager::UsbXpressDeviceManager(std::string deviceName)
{
    try
    {
        u1 = new SiLabsU1(deviceName);
    }
    catch(std::runtime_error e)
    {
        u1 = nullptr;
        throw;
    }
}

UsbXpressDeviceManager::~UsbXpressDeviceManager()
{
    delete u1;
}

/*void UsbXpressDeviceManager::connectWithSiLabsDevice()
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
}*/
#endif

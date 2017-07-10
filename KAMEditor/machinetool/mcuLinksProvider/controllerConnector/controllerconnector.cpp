#include "controllerconnector.h"
//ControllerConnector& ControllerConnector::Instance()
//{
//    static ControllerConnector m;
//    return m;
//}

ControllerConnector::ControllerConnector(const MachineTool *machineTool)
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

std::shared_ptr<UsbDevice> ControllerConnector::getU1() const
{
    return u1;
}

ControllerConnector::~ControllerConnector()
{

}

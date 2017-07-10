#ifndef CONTROLLERCONNECTOR_H
#define CONTROLLERCONNECTOR_H

//#define VENDOR_ID 0x10c4
//#define PRODUCT_ID 0xea61
//#define USB_DEBUG_LEVEL 1
//#define DATA_SIZE 64

//#include "libusb/include/libusb.h"

#include <string>
#include <QDebug>

#include "machinetool/structs.h"
#include "machinetool/mcuLinksProvider/usbDevice/usbdevice.h"
#include "machinetool/machinetool.h"

/*!
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief является оберткой над классом UsbDevice, обеспечивая его единственность;
 */
class ControllerConnector
{
private:
    //ControllerConnector();
    std::shared_ptr<UsbDevice> u1;
public:
    ControllerConnector(const MachineTool *machineTool);
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    //static ControllerConnector& Instance();
    ~ControllerConnector();
    std::shared_ptr<UsbDevice> getU1() const;
};

#endif // CONTROLLERCONNECTOR_H

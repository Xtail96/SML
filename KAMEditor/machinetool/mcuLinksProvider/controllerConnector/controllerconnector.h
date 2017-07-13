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
#include "machinetool/mcuLinksProvider/controllerConnector/usbDevice/usbdevice.h"
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
    /*!
     * \brief u1 умный указатель на контроллер u1
     */
    std::shared_ptr<UsbDevice> u1;
public:
    /*!
     * \brief Создает экземпляр класса ControllerConnector
     * \param machineTool станок, который необходимо свзять с контроллером
     */
    ControllerConnector(const MachineTool *machineTool);
    // Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    //static ControllerConnector& Instance();
    ~ControllerConnector();

    /*!
     * \brief getU1 Возвращает умный указатель на текущий контроллер u1
     * \return умный указатель на экземпляр класса UsbDevice
     */
    std::shared_ptr<UsbDevice> getU1() const;
};

#endif // CONTROLLERCONNECTOR_H

#ifndef USBDEVICESMANAGER_H
#define USBDEVICESMANAGER_H

//#define VENDOR_ID 0x10c4
//#define PRODUCT_ID 0xea61
//#define USB_DEBUG_LEVEL 1
//#define DATA_SIZE 64

//#include "libusb/include/libusb.h"

#include <string>
#include <QDebug>

#include "models/structs.h"
#include "models/controllerconnector/usbdevicesmanager/usbdevice/usbdevice.h"
#include "models/controllerconnector/usbdevicesmanager/usbdevice/u1.h"
#include "models/machinetool/machinetool.h"

/*!
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \brief является оберткой над классом UsbDevice, обеспечивая его единственность;
 */
class UsbDevicesManager
{
private:
    /*!
     * \brief u1 умный указатель на контроллер u1
     */
    std::shared_ptr<UsbDevice> u1;
public:
    /*!
     * \brief Создает экземпляр класса ControllerConnector
     * \param machineTool станок, который необходимо свзять с контроллером
     */
    UsbDevicesManager(const MachineTool *machineTool);
    ~UsbDevicesManager();

    /*!
     * \brief getU1 Возвращает умный указатель на текущий контроллер u1
     * \return умный указатель на экземпляр класса UsbDevice
     */
    std::shared_ptr<UsbDevice> getU1() const;
};

#endif // USBDEVICESMANAGER_H

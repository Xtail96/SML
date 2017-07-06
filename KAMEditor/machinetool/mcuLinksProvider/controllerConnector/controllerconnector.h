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

/*!
 * \brief Класс "Модуль взаимодействия с контроллером"
 * \warning Является синглтоном
 * \brief Класс получает данные из буфера обмена данными и следит за корректностью разрядности;
 */
class ControllerConnector
{
private:
    ControllerConnector();
public:
    //! Возвращает экземпляр класса "Модуль взаимосвязи с  контроллером"
    static ControllerConnector& Instance();

    ~ControllerConnector();
public slots:

    //! Отправляет данные на контроллер
    void send();
    void recieved();
};

#endif // CONTROLLERCONNECTOR_H

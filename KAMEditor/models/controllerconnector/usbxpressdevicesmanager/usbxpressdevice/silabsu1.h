#ifndef SILABSU1_H
#define SILABSU1_H
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.h"
#include "models/machinetool/machinetool.h"

/*!
 * \brief SiLabsU1 класс являющийся представлением контроллера u1 в системе станка
 * Наследник UsbXpressDevice
 * Осуществляет транзакции данных между системой и контроллером u1
 */
class SiLabsU1 : public UsbXpressDevice
{
public:
    SiLabsU1(MachineTool *machineTool);
    int receiveData();
    int sendData();
};

#endif // SILABSU1_H

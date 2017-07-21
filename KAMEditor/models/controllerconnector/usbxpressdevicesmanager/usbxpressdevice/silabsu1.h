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
    /*!
     * \brief GET_MCU_STATE - получить данные о состоянии станка
     */
    const unsigned char GET_MCU_STATE = 9;

    void requestReceiving();
public:
    SiLabsU1(MachineTool *machineTool);
    byte_array receiveData(int packetSize);
    unsigned int sendData(const byte_array &data);

    void displayData(const byte_array &data);
};

#endif // SILABSU1_H

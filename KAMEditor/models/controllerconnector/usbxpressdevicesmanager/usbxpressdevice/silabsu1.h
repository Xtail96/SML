#ifndef SILABSU1_H
#define SILABSU1_H

#ifdef Q_OS_WIN

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

    /*!
     * \brief Осуществляет запрос на получение данных
     */
    void requestReceiving();
public:
    /*!
     * \brief Конструктор класса SiLabsU1
     * \param machineTool - указатель на подключаемый к контроллеру станок
     */
    SiLabsU1(MachineTool *machineTool);

    /*!
     * \brief Получает данные от контроллера
     * \param packetSize - ожидаемый размер полученных данных
     * \return данные, полученные от контроллера, в формате массива байт. Для хранения байта используется тип char
     * \warning является переопределением чисто вирутального метода базового класса
     */
    byte_array receiveData(unsigned int packetSize) override;

    /*!
     * \brief Отправляет данные на контроллер
     * \param data - отправляемые данные
     * \warning является переопределением чисто вирутального метода базового класса
     */
    void sendData(const byte_array &data) override;

    /*!
     * \brief Отображает данне в консоли Qt
     * \param data - отображаемые данные
     */
    void displayData(const byte_array &data);
};
#endif

#endif // SILABSU1_H

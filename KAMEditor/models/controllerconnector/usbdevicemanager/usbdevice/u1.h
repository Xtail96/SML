#ifndef U1_H
#define U1_H

#include "usbdevice.h"

/*!
 * \brief Класс U1.
 * Является наследником абстрактного класса UsbDevice
 */
class U1 : public UsbDevice
{
private:
    /*!
     * \brief GET_MCU_STATE - получить данные о состоянии станка
     */
    const unsigned char GET_MCU_STATE = 9;

    std::vector<unsigned char> makePacket(unsigned char actionId, const std::vector<unsigned char>& params);
public:
    /*!
     * \brief Для создания объекта класса U1 необходимы идентификатор производителя(vendor id) и идентификатор продукта(product id)
     * \param _vendorId - идетификатор производителя
     * \param _productId - идентификатор продукта
     */
    U1(uint16_t _vendorId, uint16_t _productId);

    virtual std::vector<unsigned char> receiveData() override;
    virtual void sendData(unsigned char actionId, std::vector<unsigned char> params) override;

    /*!
     * \brief Метод осуществляющий очистку выбранной точки выхода
     * \param endPoint - точка выхода в щестнадцатиричной системе счисления.
     */
    void clearEndpoint(int endPoint);

    void displayData(unsigned char *data, unsigned int dataSize);

    /*!
     * \brief Отображает информацию об устройстве:
     * Номер порта, Номер шины, Адерс устройства, Скорость обмена данными
     */
    void displayDeviceInfromation();
};

#endif // U1_H

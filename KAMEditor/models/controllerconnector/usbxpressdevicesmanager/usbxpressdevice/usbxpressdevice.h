#ifndef USBXPRESSDEVICE_H
#define USBXPRESSDEVICE_H

#ifdef Q_OS_WIN

#include <QDebug>

// usbxpress
#include "dependencies.h"

typedef unsigned char byte;
typedef std::vector<byte> byte_array;

/*!
 * \brief UsbXpressDevice Класс для работы с устройствами Silicon Labs с помощью бибилиотеки USBXpress
 */
class UsbXpressDevice
{
private:
    /*!
     * \brief Находит устройство в общем списке подключенных устройств от Silicon Labs
     * \param deviceName - имя устройства
     * \param count - общее число устройств
     * \return Номер устройства с именем deviceName или -1, если устройство не найдено
     */
    int findDevice(std::string deviceName, DWORD count);

    /*!
     * \brief Подготавливает устройство Silicon Labs к работе
     * \param silabsDeviceNumber - номер устройства, может быть получен с помощью findDevice()
     */
    void setupSiLabsDevice(int silabsDeviceNumber);
protected:
    /// обработчик устройства
    HANDLE siDeviceHandle = nullptr;
public:
    UsbXpressDevice(std::string deviceName);
    ~UsbXpressDevice();

    /*!
     * \brief Инициализирует устройтсва по его имени (SI_ProductString)
     * \param deviceName - имя подключаемого устройтсва
     */
    void initialize(std::string deviceName);

    /*!
     * \brief Освобождает устройство
     */
    void free();

    /*!
     * \brief Получает данные от контроллера
     * \param packetSize - ожидаемый размер полученных данных
     * \return данные, полученные от контроллера, в формате массива байт. Для хранения байта используется тип char
     * \warning чисто виртуальный метод
     */
    virtual byte_array receiveData(unsigned int packetSize) = 0;

    /*!
     * \brief Отправляет данные на контроллер
     * \param data - отправляемые данные
     * \warning чисто виртуальный метод
     */
    virtual void sendData(const byte_array &data) = 0;

};
#endif

#endif // USBXPRESSDEVICE_H

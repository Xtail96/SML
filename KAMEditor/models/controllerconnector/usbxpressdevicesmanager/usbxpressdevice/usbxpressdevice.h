#ifndef USBXPRESSDEVICE_H
#define USBXPRESSDEVICE_H

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
};

#endif // USBXPRESSDEVICE_H

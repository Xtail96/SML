#ifndef USBXPRESSDEVICE_H
#define USBXPRESSDEVICE_H

#include <QDebug>

// usbxpress
#include "dependencies.h"

/*!
 * \brief UsbXpressDevice Класс для работы с устройствами Silicon Labs с помощью бибилиотеки USBXpress
 */
class UsbXpressDevice
{
public:
    /// обработчик устройства
    HANDLE siDeviceHandle;

    UsbXpressDevice(std::string deviceName);
    ~UsbXpressDevice();

    /*!
     * \brief Инициализирует устройтсва по его имени (SI_ProductString)
     * \param deviceName - имя подключаемого устройтсва
     */
    void initialize(std::string deviceName);

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
};

#endif // USBXPRESSDEVICE_H

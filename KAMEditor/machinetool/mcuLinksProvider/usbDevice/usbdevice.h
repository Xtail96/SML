#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <vector>
#include <QDebug>

#include "dependencies.h"

/**
 * @brief Класс для работы с usb устройствами (чтение и запись)
 */
class UsbDevice
{
private:
    /// Контекст, в котором происходит работа с libusb
    libusb_context *context = NULL;
    /// Указатель на текущее устройство
    libusb_device *device = NULL;
    /// Указатель для совершения операций ввода/вывода
    libusb_device_handle *deviceHandle = NULL;

    /**
     * @brief Инициализирует библиотеку libusb
     * \warning Если инициализация не удалась, бросает исключение runtime_error
     */
    void initialize_libusb();

    /**
     * @brief Инициализирует заданное устройство
     * @param vid vendorId устройства
     * @param pid productId устройства
     */
    void initializeDevice(uint16_t vid, uint16_t pid);

    /**
     * @brief Осуществляет поиск заданного устройства в списке всех usb устройств
     * @param vid vendorId устройства
     * @param pid productId устройства
     * @param devices список всех usb устройств
     * @param N число всех usb устройств
     * @return указатель на найденное устройство
     * \warning Если устройство не было найдено, бросает исключение runtime_error
     */
    libusb_device* findDevice(uint16_t vid, uint16_t pid, libusb_device** devices, size_t N);

    /**
     * @brief Открывает заданное устройство для чтения и записи
     * @param device заданное устройство
     * @return указатель для совершения операций ввода/вывода
     * \warning Если не удалось открыть устройство, бросает исключение runtime_error
     */
    libusb_device_handle* openDevice(libusb_device* device);

    /**
     * @brief Захватывает интерфейс для управления устройством
     * @param interfaceNumber номер захватываемого интерфейса
     * \warning Если не удалось захватить интерфейс, бросает исключение runtime_error
     */
    void claimInterface(int interfaceNumber = 0);

    /**
     * @brief Освобожадет указанный интерфейс
     * @param interfaceNumber номер освобожадаемого интерфейса
     * \warning Если не удалось освободить интерфейс, бросает исключение runtime_error
     */
    void releaseInterface(int interfaceNumber = 0);


public:
    /**
     * @brief Создает экземпляр класса для работы с заданным устройством
     * @param vendorId
     * @param productId
     */
    UsbDevice(uint16_t vendorId, uint16_t productId);
    ~UsbDevice();
};

#endif // USBDEVICE_H

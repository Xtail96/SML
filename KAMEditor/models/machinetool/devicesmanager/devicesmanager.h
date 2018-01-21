#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/machinetool/devicesmanager/device/device.h"

/*!
 * \brief Класс Менеджер устройств
 */
class DevicesManager
{
private:
    /*!
     * \brief Идентификатор установки устройств
     * Id для контроллера, сообщающий, что в последующая команда будет на включение/выключение устройств
     */
    const unsigned char SET_DEVICES = 16;

    /// Вектор умных указателей на устройства
    std::vector< std::shared_ptr<Device> > devices;

    /// Буфер устройств
    DevicesBuffer devicesBuffer;

    /*!
    * \brief Получает маску устройства
    * \param boardName - имя платы, к которой подключено устройство
    * \param portNumber - имя порта, к которому подключено устройство
    * \param outputNumber - имя выхода, к которому подключено устройство
    * \return маска устройства
    */
    byte getDeviceMask(QString boardName, unsigned int portNumber, unsigned int outputNumber);
public:
    /*!
     * \brief Конструктор класса Менеджер устройств
     */
    DevicesManager();

    /*!
     * \brief Конструктор копирования класса Менеджер устройств
     * \param object ссылка на объект класса Менеджер устройств
     */
    DevicesManager(const DevicesManager &object);

    /*!
     * \brief Возвращет ссылку на контейнер устройств
     * \return ссылка вектор устройств
     */
    std::vector<std::shared_ptr<Device> >& getDevices();

    /*!
     * \brief Возвращает буфер устройств
     * \return буфер устройств
     */
    DevicesBuffer getDevicesBuffer() const;

    /*!
     * \brief Обновляет контейнер устройств
     * \param value - константная ссылка на новый контейнер с устройствами
     */
    void updateDevices(const std::vector<std::shared_ptr<Device> > &value);

    /*!
     * \brief Инициализирует контейнер с устройствами
     */
    void initialize();

    /*!
     * \brief Формирует посылку, которую нужно послать контроллеру для включения/отключения нужного устройства
     * \param device - устройство, которое необходимо включить/выключить
     * \param onOff - true, включить устройство, false -выключить устрой ство
     * \param firstAgrument - 1 аргумент для включения/выключения устройства (по умолчанию 0x00)
     * \param secondArgument - 2 аргумент для включения/выключения устройства (по умолчанию 0x00)
     * \return послыка для контроллера включающая/отключающая устройство device с аргументами firstArgument и secondArgument
     */
    byte_array getSwitchDeviceData(const Device &device, bool onOff, byte firstAgrument = 0x00, byte secondArgument = 0x00);

    /*!
     * \brief Производит поиск устройства в списке устройств
     * \param deviceName - имя устройства
     * \return ссылка на найденное устройство
     * \warning Если устройство не найдено, бросает исключение std::invalid_argument с параметром device not found
     */
    Device& findDevice(QString deviceName);
};

#endif // DEVICESMANAGER_H

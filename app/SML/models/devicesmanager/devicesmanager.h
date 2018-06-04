#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/devicesmanager/device/device.h"

/*!
 * \brief Структура Буфер устройств
 */
struct DevicesBuffer
{
private:
    /// текущее состояние всех устройств
    byte devicesState = 0xff;

    /*!
     * \brief Инвертирует байт
     * \param byte - байт
     * \return инвертированный байт
     */
    byte invertByte(byte byte)
    {
        return byte ^ 0xff;
    }
public:

    /*!
     * \brief Конструктор структуры Буфер устройств
     * Инициализиурет состояние всех устройств единицами
     */
    DevicesBuffer()
    {
        devicesState = 0xff;
    }

    /*!
     * \brief Формирует нужную маску для включения/выключения устройства
     * \param deviceMask - маска включения устройства
     * \param deviceState - true, устройство включено, false - иначе
     * \return маска включения/выключения устройства
     */
    byte getDevicesMask(byte deviceMask, bool deviceState)
    {
        qDebug() << "origin: " + QString::number(deviceMask, 2);
        if(deviceState == false)
        {
            devicesState = devicesState & deviceMask;
        }
        else
        {
            deviceMask = invertByte(deviceMask);
            qDebug() << "invert:" + QString::number(deviceMask, 2);
            devicesState = devicesState | deviceMask;
        }
        qDebug() << "Devices state =" << QString::number(devicesState, 2);
        return devicesState;
    }

    /*!
     * \brief Возвращает текущее состояние устройств
     * \return ссылка на байт с текущим состоянием устройств
     */
    byte &getDevicesState()
    {
        return devicesState;
    }

    /*!
     * \brief Устанавливает новое состояние устройств
     * \param value - байт с новым состоянием устройств
     */
    void setDevicesState(const byte &value)
    {
        if(devicesState != value)
        {
            devicesState = value;
        }
    }

    bool getDeviceState(byte deviceMask)
    {
        bool enable = false;
        if(devicesState != 0x00)
        {
            enable = ((devicesState & deviceMask) == devicesState);
        }
        return enable;
    }
};


/*!
 * \brief Класс Менеджер устройств
 */
class DevicesManager
{
protected:
    /*!
     * \brief Идентификатор установки устройств
     * Id для контроллера, сообщающий, что в последующая команда будет на включение/выключение устройств
     */
    const unsigned char SET_DEVICES = 16;

    /// Вектор умных указателей на устройства
    QList< QSharedPointer<Device> > m_devices;

    /// Буфер устройств
    DevicesBuffer m_devicesBuffer;

    /*!
    * \brief Получает маску устройства
    * \param boardName - имя платы, к которой подключено устройство
    * \param portNumber - имя порта, к которому подключено устройство
    * \param outputNumber - имя выхода, к которому подключено устройство
    * \return маска устройства
    */
    byte deviceMask(QString boardName, unsigned int portNumber, unsigned int outputNumber);

    /*!
     * \brief Инициализирует контейнер с устройствами
     * \param sm - менеджер настроек
     */
    void initialize(const SettingsManager &sm);

public:
    /*!
     * \brief Конструктор класса Менеджер устройств
     * \param sm - менеджер настроек
     */
    DevicesManager(const SettingsManager &sm = SettingsManager());

    /*!
     * \brief Конструктор копирования класса Менеджер устройств
     * \param object - ссылка на объект класса Менеджер устройств
     */
    DevicesManager(const DevicesManager &object);

    /*!
     * \brief Возвращет ссылку на контейнер устройств
     * \return ссылка вектор устройств
     */
    QList<QSharedPointer<Device> >& devices();

    /*!
     * \brief Возвращает буфер устройств
     * \return буфер устройств
     */
    DevicesBuffer devicesBuffer() const;

    /*!
     * \brief Обновляет контейнер устройств
     * \param value - константная ссылка на новый контейнер с устройствами
     */
    void updateDevices(const QList<QSharedPointer<Device> > &value);

    void updateDevices(const byte_array devicesState);

    /*!
     * \brief Формирует посылку, которую нужно послать контроллеру для включения/отключения нужного устройства
     * \param device - устройство, которое необходимо включить/выключить
     * \param onOff - true, включить устройство, false -выключить устрой ство
     * \param firstAgrument - 1 аргумент для включения/выключения устройства (по умолчанию 0x00)
     * \param secondArgument - 2 аргумент для включения/выключения устройства (по умолчанию 0x00)
     * \return послыка для контроллера включающая/отключающая устройство device с аргументами firstArgument и secondArgument
     */
    byte_array switchDeviceData(const Device &device, bool onOff, byte firstAgrument = 0x00, byte secondArgument = 0x00);

    /*!
     * \brief Производит поиск устройства в списке устройств
     * \param deviceName - имя устройства
     * \return ссылка на найденное устройство
     * \warning Если устройство не найдено, бросает исключение std::invalid_argument с параметром device not found
     */
    Device& findDevice(QString deviceName);

    /*!
     * \brief Возвращает названия всех устройств для вывода в интерфейс
     * \return названия всех устройств в формате списка QStringList
     */
    QStringList devicesNames();

    /*!
     * \brief Возвращает названия параметров устройств для вывода в интерфейс
     * \return названия параметров устройств в формате списка QStringList
     */
    QStringList devicesParametrsNames();

    /*!
     * \brief Возвращает настройки всех устройств для вывода в интерфейс
     * \return настройки устройств в формате QList<QStringList>
     */
    QList<QStringList> devicesSettings();

    /*!
     * \brief Возвращает названия устройств, которые необходимо отображать в Наладке
     * \return названия устройств для отображения в Наладке в виде списка QStringList
     */
    QStringList onScreenDevicesNames();

    /*!
     * \brief Возвращает состояние (включено/выключено) устройств, которые необходимо отображать в Наладке
     * \return состояние (включено/выключено) каждого устройства, необходимого для отображения в Наладке в виде списка QList<bool>
     */
    QList<bool> onScreenDevicesStates();
};

#endif // DEVICESMANAGER_H

#ifndef DEVICESMANAGER_H
#define DEVICESMANAGER_H
#include <vector>
#include <memory>

#include "models/devicesmanager/device/spindel.h"
#include "models/devicesmanager/device/supportdevice.h"

/*!
 * \brief Структура Буфер устройств
 */
struct DevicesBuffer
{
public:

    /*!
     * \brief Конструктор структуры Буфер устройств
     * Инициализиурет состояние всех устройств единицами
     */
    DevicesBuffer(size_t size = 1) :
        m_devicesState(byte_array(size, 0xff))
    {
    }

    /*!
     * \brief Формирует нужную маску для включения/выключения устройства
     * \param deviceMask - маска включения устройства
     * \param deviceState - true, устройство включено, false - иначе
     * \return маска включения/выключения устройства
     */
    /*byte getDevicesMask(byte deviceMask, bool deviceState)
    {
        qDebug() << "origin: " + QString::number(deviceMask, 2);
        if(deviceState == false)
        {
            m_devicesState[0] = m_devicesState[0] & deviceMask;
        }
        else
        {
            deviceMask = invertByte(deviceMask);
            qDebug() << "invert:" + QString::number(deviceMask, 2);
            m_devicesState[0] = m_devicesState[0] | deviceMask;
        }
        qDebug() << "Devices state =" << QString::number(m_devicesState[0], 2);
        return m_devicesState[0];
    }*/

    /*!
     * \brief Возвращает текущее состояние устройств
     * \return ссылка на байт с текущим состоянием устройств
     */
    /*byte &getDevicesState()
    {
        return m_devicesState;
    }*/

    /*!
     * \brief Устанавливает новое состояние устройств
     * \param value - байт с новым состоянием устройств
     */
    /*void setDevicesState(const byte &value)
    {
        if(m_devicesState != value)
        {
            m_devicesState = value;
        }
    }

    bool getDeviceState(byte deviceMask)
    {
        bool enable = false;
        if(m_devicesState != 0x00)
        {
            enable = ((m_devicesState & deviceMask) == m_devicesState);
        }
        return enable;
    }*/

private:
    /// текущее состояние всех устройств
    byte_array m_devicesState;

    /*!
     * \brief Инвертирует байт
     * \param byte - байт
     * \return инвертированный байт
     */
    /*byte invertByte(byte byte)
    {
        return byte ^ 0xff;
    }*/
};


/*!
 * \brief Класс Менеджер устройств
 */
class DevicesManager
{
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

    void updateDevices(const byte_array devicesState);

    QStringList getDeviceSwitchParams(size_t index, bool onOff);

    /*!
     * \brief Возвращает названия всех устройств для вывода в интерфейс
     * \return названия всех устройств в формате списка QStringList
     */
    QStringList getAllDevicesNames();

    /*!
     * \brief Возвращает названия параметров устройств для вывода в интерфейс
     * \return названия параметров устройств в формате списка QStringList
     */
    QStringList getDevicesParametrsNames();

    /*!
     * \brief Возвращает настройки всех устройств для вывода в интерфейс
     * \return настройки устройств в формате QList<QStringList>
     */
    QList<QStringList> getDevicesSettings();

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

    QList<Spindel> getSpindels();
    Spindel& findSpindel(QString name);
    QStringList getSwitchSpindelParams(QString name);
    void setSpindelRotations(QString name, size_t rotations);

protected:
    QList< QSharedPointer<Spindel> > m_spindels;
    QList< QSharedPointer<SupportDevice> > m_supportDevices;

    /// Буфер устройств
    DevicesBuffer m_devicesBuffer;

    /*!
     * \brief Инициализирует контейнер с устройствами
     * \param sm - менеджер настроек
     */
    void initialize(const SettingsManager &sm);


    Device& findDevice(size_t index);
};

#endif // DEVICESMANAGER_H

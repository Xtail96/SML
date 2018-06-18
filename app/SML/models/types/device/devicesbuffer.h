#ifndef DEVICESBUFFER_H
#define DEVICESBUFFER_H

#include <QObject>
#include "models/types/structs.h"

class DevicesBuffer : public QObject
{
    Q_OBJECT
public:
    DevicesBuffer(QObject* parent = nullptr);
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

#endif // DEVICESBUFFER_H

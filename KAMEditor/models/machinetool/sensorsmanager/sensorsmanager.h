#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/machinetool/sensorsmanager/sensor/sensor.h"

/// Необходимые для работы с датчиками структуры

/*!
 * \brief Структура "Буффер состояний"
 *  Содержит информацию о состоянии систем станка
 */
struct SensorsBuffer
{
public:
    /*!
     * \brief buffer - содержит всю информацию о состояниях датчиков станка
     */
    byte_array buffer;

    /*!
     * \brief portalFirstPortSensors - содержит информацию о состоянии датчиков 1 порта портальной платы
     */
    byte portalFirstPortSensors;

    /*!
     * \brief Обновляет состояние буфера обмена данными
     * \param value - новое значение буфера
     */
    void updateBuffer(byte_array value)
    {
        if(value.size() >= 16)
        {
            buffer = value;
            if(isSensorsStateChanged(portalFirstPortSensors, value[2]))
            {
                portalFirstPortSensors = buffer[2];
            }
        }
    }

    /*!
     * \brief Проверяет изменилось ли состояние группы датчиков
     * \param currentState - байт, содержащий текущее состояние датчиков
     * \param newState - байт, содержащий новое значение состояний датчиков
     * \return true, если состояние изменилось, false - иначе
     */
    bool isSensorsStateChanged(byte currentState, byte newState)
    {
        bool sensorsStateChanged = false;
        if(currentState != newState)
        {
            sensorsStateChanged = true;
        }
        return sensorsStateChanged;
    }

    /*!
     * \brief Проверяет активен ли датчик
     * \param plateName - имя платы, к которой подключен датчик
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool getSensorState(QString plateName, unsigned int portNumber, unsigned int inputNumber) const
    {
        bool enable = false;
        if(plateName == "portal")
        {
            enable = checkSensorState(portNumber, inputNumber);
        }
        return enable;
    }

private:
    /*!
     * \brief Проверяет состояние датчика
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool checkSensorState(unsigned int portNumber, unsigned int inputNumber) const
    {
        bool isVoltage = true;
        byte tmp = portalFirstPortSensors;

        switch(portNumber) {
        case 1:
        {
            // сдвигаем все биты влево, чтобы исключить все биты слева, а нужный бит стоял в старшем разряде
            tmp = tmp << (7-inputNumber);

            // сдвигаем все биты вправо, чтобы все биты слева стали нулями, а нужный бит находился в младшем разряде
            tmp = tmp >> 7;

            if(tmp == 0x00)
            {
                isVoltage = false;
            }
            break;
        }
        default:
            break;
        }
        return isVoltage;
    }
};


/*!
 * \brief Класс "Менеджер датчиков"
 */
class SensorsManager
{
protected:
    /*!
     * \brief Вектор умных указателей на датчики станка
     */
    std::vector< std::shared_ptr<Sensor> > sensors;

    SensorsBuffer m_buffer;

    /*!
     * \brief Инициализирует датчики по файлу настроек
     * \param sm - указатель на менеджер настроек
     */
    void initilize(SettingsManager *sm);

public:
    /*!
     * \brief Конструктор класса "Менеджер датчиков"
     * \param sm - указатель на менеджер настроек (по умолчанию nullptr)
     */
    SensorsManager(SettingsManager *sm = nullptr);

    /*!
     * \brief Конструктор копирования класса Менеджер датчиков
     * \param object - ссылка на объект класса Менеджер датчиков
     */
    SensorsManager(const SensorsManager &object);

    /*!
     * \brief Возвращает ссылку на датчики станка
     * \return вектор умных указателей на датчики станка
     */
    std::vector<std::shared_ptr<Sensor> > &getSensors();

    /*!
     * \brief Обновляет состояния датчиков по буферу состояний станка
     * \param buffer - буфер состояний станка
     */
    void updateSensors(const SensorsBuffer buffer);

    void updateSensors(const byte_array sensorsState);
};

#endif // SENSORSMANAGER_H

#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include <map>
#include <vector>

#include "models/sensorsmanager/sensor/sensor.h"

/// Необходимые для работы с датчиками структуры

/*!
 * \brief Структура Буфер датчиков
 * Содержит информацию о состоянии датчиков станка
 * Рекоменуется всю работу с датчиками выполнять на контроллере U1.
 * А особо важные датчики, которые требуется анализировать в первую очередь,
 * подключать к портальной плате, размещаемой прямо на станине станка.
 */
struct SensorsBuffer
{
public:
    /*!
     * \brief Обновляет состояние буфера обмена данными
     * \param value - новое значение буфера
     */
    void updateBuffer(byte_array value)
    {
        if(value.size() >= m_buffer.size())
        {
            m_buffer = value;
        }
        else
        {
            qDebug() << "can not update buffer" << m_buffer.size() << " > " << value.size();
        }
    }

    /*!
     * \brief Проверяет изменилось ли состояние порта
     * \param currentState - байт, содержащий текущее состояние порта
     * \param newState - байт, содержащий новое значение состояния порта
     * \return true, если состояние изменилось, false - иначе
     */
    bool isPortStateChanged(byte currentState, byte newState)
    {
        bool sensorsStateChanged = false;
        if(currentState != newState)
        {
            sensorsStateChanged = true;
        }
        return sensorsStateChanged;
    }

    /*!
     * \brief Проверяет активен ли вход
     * \param plateName - имя платы, к которой подключен датчик (Доступные имена: "u1", "u2", "portal")
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool getInputState(QString plateName, unsigned int portNumber, unsigned int inputNumber) const
    {
        bool voltage = false;
        if(plateName == "portal")
        {
            voltage = checkPortalSensorState(portNumber, inputNumber);
        }
        else
        {
            if(plateName == "u1")
            {
                voltage = checkU1SensorState(portNumber, inputNumber);
            }
            else
            {
                if(plateName == "u2")
                {
                    // todo
                }
            }
        }
        return voltage;
    }


    /*!
     * \brief Заполняет буфер нулями
     * \param size - необходимый размер буфера
     */
    void resetBuffer(size_t size)
    {
        m_buffer = byte_array(size, 0);
    }

protected:
    /*!
     * \brief buffer - содержит всю информацию о состояниях датчиков станка
     * Размер буфера должен составлять не менее 2 байт.
     * Каждый байт представляет собой состояние какого-либо порта.
     * К одному порту может быть подключено до 8 датчиков.
     * Таким образом, максимальное число поддерживаемых датчиков равно buffer_size * 8.
     * Описание структуры буфера
     * buffer[0] - датчики 0 порта портальной платы (1 байт)
     * buffer[1] - датчики 1 порта портальной платы (1 байт)
     * buffer[2] - датчики 2 порта портальной платы (1 байт)
     * buffer[3] - датчики 3 порта портальной платы (1 байт)
     * buffer[4] - датчики 4 порта портальной платы (1 байт)
     * buffer[5] - датчики 5 порта портальной платы (1 байт)
     * buffer[6] - датчики 6 порта портальной платы (1 байт)
     * buffer[7] - датчики 7 порта портальной платы (1 байт)
     * buffer[8] - датчики 0 порта U1 (1 байт)
     * buffer[9] - датчики 1 порта U1 (1 байт)
     * buffer[10] - датчики 2 порта U1 (1 байт)
     * buffer[11] - датчики 3 порта U1 (1 байт)
     * buffer[12] - датчики 4 порта U1 (1 байт)
     * buffer[13] - датчики 5 порта U1 (1 байт)
     * buffer[14] - датчики 6 порта U1 (1 байт)
     * buffer[15] - датчики 7 порта U1 (1 байт)
     * Если размер буфера будет меньше станартного размера (16 байт),
     * то структура выше определяет, какие порты портальной платы и контроллера U1 не будут задействованы.
     * Если размер буфера будет больше, то данные с 17 байта и дальше  будут игнорироваться.
     */
    byte_array m_buffer;

    /*!
     * \brief Функция для стандартной проверки состояния датчика
     * Проверяет только наличие напряжения на входе. Т.е. true - напряжение есть. false - напряжения нет.
     * \warning Не определяет включен датчик или выключен!
     * Применима, если номер входа датчика = номеру бита в байте, кодирующем состояние группы датчиков.
     * Нумерация в байте порта должна идти с младшего разряда и, начинаться, с нуля.
     * Пример:
     * 1111[1]11
     * В данном случае, датчик, состояние которого выделено [], подключен к 1 порту и 2 входу портальной платы.
     * \param inputNumber - номер входа, к которому подключен датчик
     * \param portState - состояние порта, к которому подключен датчик
     * \return есть ли напряжение на входе
     */
    bool standardInputStateCheck(size_t inputNumber, byte portState) const
    {
        bool voltage = true;

        byte tmp = portState;
        // сдвигаем все биты влево, чтобы исключить все биты слева, а нужный бит стоял в старшем разряде
        tmp = tmp << (7-inputNumber);

        // сдвигаем все биты вправо, чтобы все биты слева стали нулями, а нужный бит находился в младшем разряде
        tmp = tmp >> 7;

        if(tmp == 0x00)
        {
            voltage = false;
        }
        else
        {
            if(tmp == 0x01)
            {
                voltage = true;
            }
        }

        return voltage;
    }

    /*!
     * \brief Проверяет состояние датчика Портальной платы
     * Проверяет только наличие напряжения на входе. Т.е. true - напряжение есть. false - напряжения нет.
     * \warning Не определяет включен датчик или выключен!
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool checkPortalSensorState(unsigned int portNumber, unsigned int inputNumber) const
    {
        bool voltage = true;

        switch(portNumber) {
        case 0:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[0]);
            break;
        }
        case 1:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[1]);
            break;
        }
        case 2:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[2]);
            break;
        }
        case 3:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[3]);
            break;
        }
        case 4:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[4]);
            break;
        }
        case 5:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[5]);
            break;
        }
        case 6:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[6]);
            break;
        }
        case 7:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[7]);
            break;
        }
        default:
            break;
        }
        return voltage;
    }

    /*!
     * \brief Проверяет состояние датчика, подключенного к U1
     * Проверяет только наличие напряжения на входе. Т.е. true - напряжение есть. false - напряжения нет.
     * \warning Не определяет включен датчик или выключен!
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool checkU1SensorState(unsigned int portNumber, unsigned int inputNumber) const
    {
        bool voltage = true;

        switch(portNumber) {
        case 0:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[8]);
            break;
        }
        case 1:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[9]);
            break;
        }
        case 2:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[10]);
            break;
        }
        case 3:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[11]);
            break;
        }
        case 4:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[12]);
            break;
        }
        case 5:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[13]);
            break;
        }
        case 6:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[14]);
            break;
        }
        case 7:
        {
            voltage = standardInputStateCheck(inputNumber, m_buffer[15]);
            break;
        }
        default:
            break;
        }
        return voltage;
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
    QList< QSharedPointer<Sensor> > m_sensors;

    SensorsBuffer m_sensorsBuffer;

    /*!
     * \brief Инициализирует датчики по файлу настроек
     * \param sm - указатель на менеджер настроек
     */
    void initialize(const SettingsManager &sm);

public:
    /*!
     * \brief Конструктор класса "Менеджер датчиков"
     * \param sm - указатель на менеджер настроек (по умолчанию nullptr)
     */
    SensorsManager(const SettingsManager &sm = SettingsManager());

    /*!
     * \brief Конструктор копирования класса Менеджер датчиков
     * \param object - ссылка на объект класса Менеджер датчиков
     */
    SensorsManager(const SensorsManager &object);

    /*!
     * \brief Возвращает ссылку на датчики станка
     * \return вектор умных указателей на датчики станка
     */
    QList< QSharedPointer<Sensor> > &sensors();

    /*!
     * \brief Обновляет состояния датчиков по буферу состояния датчиков
     * \param buffer - буфер состояний станка
     */
    void updateSensors(const SensorsBuffer buffer);

    /*!
     * \brief Обновляет состояния датчиков по массиву байт
     * \param sensorsState - состояния всех датчиков станка
     */
    void updateSensors(const byte_array sensorsState);

    /*!
     * \brief Возвращает true, если датчик с заданным именем сработал или false, если датчик не сработал.
     * \param sensorName - имя датчика (НЕ подпись!).
     * \return true, если датчик сработал или false, если датчик не сработал
     */
    bool sensorStateByName(QString sensorName);

    /*!
     * \brief Возвращает подписи для всех датчиков в виде списка для вывода в итерфейс
     * \return подписи датчиков в формате QStringList
     */
    QStringList sensorsLabels();

    /*!
     * \brief Возвращает названия параметров датчика в виде списка для вывода в интерфейс
     * \return названия параметров датчика в формате QStringList
     */
    QStringList sensorParametrLabels();

    /*!
     * \brief Возвращает настройки каждого датчика для вывода в интерфейс
     * \return настройки всех датчиков в формате QList<QStringList>
     */
    QList<QStringList> sensorsSettings();

    /*!
     * \brief Возвращает состояние "светодиода" для каждого датчика для вывода в интерфейс
     * \return "светодиоды" всех датчиков в формате QList<QColor>
     */
    QList<QColor> sensorsLeds();
};

#endif // SENSORSMANAGER_H

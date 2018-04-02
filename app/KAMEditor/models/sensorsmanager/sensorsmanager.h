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
        if(value.size() >= 16)
        {
            buffer = value;
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
            voltage = checkPortalSensorState(portNumber, inputNumber, buffer[2]);
        }
        else
        {
            if(plateName == "u1")
            {
                // todo
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

protected:
    /*!
     * \brief buffer - содержит всю информацию о состояниях датчиков станка
     * Размер буфера составляет 16 байт.
     * Каждый байт представляет собой состояние какого-либо порта.
     * К одному порту может быть подключено до 8 датчиков.
     * Таким образом, максимальное число поддерживаемых датчиков равно 16 * 8 = 128.
     * Описание структуры буффера
     * buffer[2] - байт, содержащий информацию о состоянии датчиков 1 порта портальной платы
     */
    byte_array buffer;

    /*!
     * \brief Функция для стандартной проверки состояния датчика
     * Проверяет только наличие напряжения на входе. Т.е. true - напряжение есть. false - напряжения нет.
     * \warning Не определяет включен датчик или выключен!
     * Применима, если номер входа датчика = номеру бита в байте, кодирующем состояние группы датчиков.
     * Нумерация в байте порта должна идти с младшего разряда и, начиная, с единицы.
     * Пример:
     * 1111[1]11
     * В данном случае, датчик, состояние которого выделено [], подключен к 1 порту и 3 входу портальной платы.
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
     * \param portNumber - номер порта, к которому подключен датчик
     * \param inputNumber - номер входа, к которому подключен датчик
     * \param portState - байт, в котором содержится состояние всех датчиков, нужного порта
     * \return true, если есть напряжение на входе, false - иначе
     */
    bool checkPortalSensorState(unsigned int portNumber, unsigned int inputNumber, byte portState) const
    {
        bool voltage = true;

        switch(portNumber) {
        case 1:
        {
            voltage = standardInputStateCheck(inputNumber, portState);
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
    std::vector< std::shared_ptr<Sensor> > m_sensors;

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
    std::vector<std::shared_ptr<Sensor> > &sensors();

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

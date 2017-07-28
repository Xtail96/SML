#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>
#include <map>

#include <QDebug>

typedef unsigned char byte;
typedef std::vector<byte> byte_array;

struct VectorDouble
{
    double x;
    double y;
    double z;

    double a;
    double b;

    VectorDouble(double _x = 0, double _y = 0, double _z = 0, double _a = 0, double _b = 0) : x(_x), y(_y), z(_z), a(_a), b(_b) {}
};

/*!
 * \brief Объект "Имена осей"
 * \brief Данная структура содержит список всех доступных осей и их имен для использования в системе управления.
 * \warning Имена оси - заглавне латинские буквы;
 * \warning Даная структура не имеет имени и существует только один объект "axisNames" такого типа;
 *
 * Способы взаимодействия со структурой:
 * 1) Получения имени оси(значения) по ее индексу(ключу);
 * 2) Получения индекса оси(ключа) по ее имени(значению);
 */
struct
{
    /// \details Словарь имен всех осей в формате <ключ, значение> = <индекс оси, имя оси>
    std::map<unsigned int, std::string> axisNames =
    {
        {0, "X"},
        {1, "Y"},
        {2, "Z"},
        {3, "A"},
        {4, "B"},
        {5, "C"},
        {6, "D"},
        {7, "E"},
        {8, "F"},
        {9, "G"},
        {10, "H"},
    };

    /// \details Получение имени оси(значения) по ключу(индексу);
    std::string getNameByKey(const unsigned int &value)
    {
        if(value < axisNames.size())
        {
            return axisNames[value];
        }
        else
        {
            throw std::invalid_argument("Axis does not exist");
        }
    }

    /// \details Получение индекса(ключа) по имени оси(значению);
    int getKeyByName(const std::string &s) const
    {
        int axisNumber = -1;
        for(auto it : axisNames)
        {
            if(it.second == s)
            {
                axisNumber =  it.first;
                break;
            }
        }
        if(axisNumber != -1)
        {
            return axisNumber;
        }
        else
        {
            throw std::invalid_argument("Unknown Axis");
        }
    }
} axisesNames;


/*!
 * \brief Структура "Буффер состояний"
 *  Содержит информацию о состоянии систем станка
 */
struct StatesBuffer
{
public:
    /*!
     * \brief buffer - содержит всю информацию о состояниях датчиков и устройств станка
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
    bool getSensorState(std::string plateName, unsigned int portNumber, unsigned int inputNumber) const
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
#endif // VECTOR_H

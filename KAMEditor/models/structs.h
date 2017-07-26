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

struct StateBuffer
{
    byte_array buffer;
    byte axisesStateSensors;
    void setBuffer(byte_array value)
    {
        if(value.size() >= 16)
        {
            buffer = value;
            if(checkMachineToolStateChanged(value[2]))
            {
                axisesStateSensors = buffer[2];
            }
        }
    }

    bool checkMachineToolStateChanged(byte value)
    {
        bool isMachineToolStateChanged = false;
        if(axisesStateSensors != value)
        {
            isMachineToolStateChanged = true;
        }
        return isMachineToolStateChanged;
    }

    bool isActive(std::string plateName, unsigned int portNumber, unsigned int inputNumber)
    {
        bool isActive = false;
        if(plateName == "portal")
        {
            isActive = findValueInAxisesStateSensors(portNumber, inputNumber);
        }
        return isActive;
    }

    bool findValueInAxisesStateSensors(unsigned int portNumber, unsigned int inputNumber)
    {
        bool isEnable = false;
        switch (portNumber) {
        case 1:
        {
            switch (inputNumber) {
            case 0:
                if(axisesStateSensors % 2 == 0)
                {
                    isEnable = true;
                }
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
        return isEnable;
    }
};
#endif // VECTOR_H

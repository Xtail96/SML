#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>
#include <map>


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
} axisNames;

struct DeviceBuffer
{
   std::vector<unsigned int> buffer;

   DeviceBuffer() :
       buffer(std::vector<unsigned int>(6, 0))
   {

   }

   DeviceBuffer(const std::vector<unsigned int> &value)
   {
       updateDeviceBuffer(value);
   }

   void clearDeviceBuffer()
   {
       buffer =
       {
           0, // номер выхода
           0, // код ошибки
           0, // включено ли устройство
           0, // необходимое действие: включить/выключть
           0, // аргумент устройства;
           0, // пауза
       };
   }

   std::vector<unsigned int>getDeviceBuffer() const
   {
       return buffer;
   }

   void updateDeviceBuffer(const std::vector<unsigned int> &value)
   {
       if(buffer.size() == value.size())
       {
           buffer = value;
       }
       else
       {
           if(buffer.size() < value.size())
           {
               for(unsigned int i = 0; i < buffer.size(); i++)
               {
                   buffer[i] = value[i];
               }
           }
           else
           {
               unsigned int difference = buffer.size() - value.size();
               buffer = value;
               for(unsigned int i = 0; i< difference; i++)
               {
                   buffer.push_back(0);
               }
           }
       }
   }
};

struct SensorBuffer
{
    std::vector<unsigned int> buffer;
    SensorBuffer()
    {
        std::vector<unsigned int> buffer =
        {
            0, // номер входа
            0, // активен ли датчик
        };
    }
};

/// Настройки KFlop
//struct AxisKFlopSettings
//{
//    double jerk;
//    double acceleration;
//    double velocity;
//    int channel;
//    double basingVelocity;
//    AxisKFlopSettings(double _jerk = 0, double _acceleration = 0, double _velocity = 0, int _channel = 0, double _basingVelocity = 0)
//        : jerk(_jerk), acceleration(_acceleration), velocity(_velocity), channel(_channel), basingVelocity(_basingVelocity){}
//};
#endif // VECTOR_H

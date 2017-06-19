#ifndef POINT_H
#define POINT_H
#include <vector>

#include "machinetool/structs.h"
#include "machinetool/machinetool.h"

//typedef VectorDouble Point;

/*!
 * \brief Класс "Точка"
 * \brief Данный класс содержит данные о координатах точки по каждой из существуюущих осей станка и обеспечивает взаимодействие с координатами точки.
 *
 * Способы взаимодействия с классом:
 * 1) Добавление точки;
 * 2) Получение значения координаты точки по опредеоенной оси по имени соответствующей оси;
 * 3) Осуществление взаимодействия(получени/установка) с вектором координат точки;
 */
struct Point{
    //! Вектор, содержащий координаты точки по осям станка;
    std::vector<double> coordinates;

    //! Пустой конструктор
    /// \details создает точку с нулевыми координатами по всем существующим осям станка
    Point()
    {
        MachineTool &instance = MachineTool::Instance();
        int axisCount = instance.getAxisCount();
        coordinates = std::vector<double>(axisCount);
    }

    //! Конструктор по вектору значений
    /**
     * Создает точку с указанными в вкторе координатами;
     * Если число координат в передаваемом векторе, превышает число существующих осей станка, из вектора координат будут взяты первые n элементов, где n - число существующих осей станка;
     * Если число координат в передаваемом векторе, меньше чем число существующих осей станка, координаты по остальным осям станка будут установлены в нулевые;
     */
    Point(std::vector<double> _coordinates)
    {
        MachineTool &instance = MachineTool::Instance();
        unsigned int axisCount = instance.getAxisCount();
        if(axisCount == _coordinates.size())
        {
            coordinates = _coordinates;
        }
        else
        {
            if(axisCount > _coordinates.size())
            {
                unsigned int difference = axisCount - _coordinates.size();
                coordinates = _coordinates;
                for(unsigned int i = 0; i < difference; i++)
                {
                    coordinates.push_back(0);
                }
            }
            else
            {
                for(unsigned int i = 0; i < axisCount; i++)
                {
                    coordinates.push_back(_coordinates[i]);
                }
            }
        }
    }

    //! Методы получения и установки значений:
    /// \details Метод получения координат точки в формате вектора;
    std::vector<double> getCoordinates() const
    {
        return coordinates;
    }

    /**
     * Метод для утсановки координат точки по вектору координат.
     * Если число координат в передаваемом векторе больше, чем число существующих координат точки, будет присвоено только первые n координат, где n - число существующих координат точки;
     * Если число координат в передаваемом векторе меньше, чем число существующих координат точки, после установки n координат, где n - число координат в передаваемом векторе, координаты точки по остальным осям остануться без изменений;
     **/
    void setCoordinates(const std::vector<double> &value)
    {
        if(coordinates.size() == value.size())
        {
            coordinates = value;
        }
        else
        {
            if(coordinates.size() > value.size())
            {
                for(unsigned int i = 0; i < value.size(); i++)
                {
                    coordinates[i] = value[i];
                }
            }
            else
            {
                for(unsigned int i = 0; i< coordinates.size(); i++)
                {
                    coordinates[i] = value[i];
                }
            }
        }
    }

    //! Оператор [] позволяет обращаться к координате оси по соответствующему имени
    double operator[](std::string s)
    {
        unsigned int i = axisNames.getKeyByName(s);
        return coordinates[i];
    }
};


#endif // POINT_H


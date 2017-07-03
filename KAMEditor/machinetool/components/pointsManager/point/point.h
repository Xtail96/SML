#ifndef POINT_H
#define POINT_H

#include <vector>
#include "machinetool/structs.h"

/**
 * @brief Класс "Точка"
 *
 * Содержит координаты типа double по каждой из осей станка
 */
class Point
{
private:
    /// Массив, где хранятся координаты
    std::vector<double> coordinates;

public:
    /**
     * @brief Создает точку заданной размерности и инициализирует каждую координату нулем
     * @param dimension размерность точки
     */
    Point(int dimension = 3);

    /**
     * @brief Создает точку с явно заданными координатами, размерность равна числу заданных координат
     * @param coords явно заданные координаты
     *
     * Пример использования:
     *
     * \code{.cpp}
     * Point p = {1.5, 0.33, -3.66, 1, 0};
     * \endcode
     */
    Point(std::initializer_list<double> coords);

    /**
     * @brief Получение конкретной координаты по заданному номеру
     * @param idx номер координаты
     * @return ссылку на координату
     * \warning Если номер превышает число координат, бросает исключение out_of_range
     *
     * Пример использования:
     *
     * \code{.cpp}
     * double x = point[1];
     * \endcode
     */
    double& operator[](size_t idx);

    /**
     * @brief Получение конкретной координаты по заданному имени оси
     * @param name имя оси
     * @return ссылку на координату
     * \warning Если оси с таким именем не существует, бросает исключение invalid_argument
     * \warning Может бросать исключение out_of_range (см. получение координаты по номеру)
     *
     * Пример использования:
     * \code{.cpp}
     * double a = point["A"];
     * \endcode
     *
     * \see Point::operator[](size_t idx);
     */
    double& operator[](std::string name);

    /**
     * @brief Операторы проверки точек на равенство
     * @param other точка, с которой сравнивается текущая точка
     * @return true, если точки равны (оператор ==), либо не равны (оператор !=), иначе false
     */
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    /**
     * @brief Домножает текущую точку на заданный коэффициент
     * @param x коэффициент, на который домножится текущая точка
     * @return полученная в результате домножения точка
     *
     * Пример использования:
     * \code{.cpp}
     * point *= 1.5;
     * \endcode
     */
    Point& operator*=(double x);
};

/**
 * @brief Умножает заданную точку на заданный коэффициент слева
 * @param x коэффициент
 * @param p точка
 * @return точка, полученная в результате умножения
 *
 * Пример использования:
 * \code{.cpp}
 * Point result = 1.5 * point;
 * \endcode
 */

Point operator*(double x, Point p);
/**
 * @brief Умножает заданную точку на заданный коэффициент справа
 * @param p точка
 * @param x коэффициент
 * @return точка, полученная в результате умножения
 *
 * Пример использования:
 * \code{.cpp}
 * Point result = point * 1.5;
 * \endcode
 */
Point operator*(Point p, double x);

#endif // POINT_H


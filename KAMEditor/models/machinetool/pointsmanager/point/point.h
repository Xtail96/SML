#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <algorithm>
#include <vector>

#include "models/structs.h"

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
     * @brief Создает точку по заданному вектору координат
     * @param v вектор координат
     */
    Point(const std::vector<double>& v);

    /**
     * @brief Создает копию заданной точки
     * @param other копируемая точка
     */
    Point(const Point& other);

    /**
     * @brief Присваивает данной точке значение другой точки
     * @param other новое значение точки
     * @return ссылка на текущую точку
     */
    Point& operator=(Point other);

    /**
     * @brief Получение конкретной координаты по заданному номеру
     * @param idx номер координаты
     * @return ссылку на координату
     * \warning Если номер превышает число координат, бросает исключение out_of_range
     *
     * Пример использования:
     *
     * \code{.cpp}
     * double x = point[3];
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
     * @brief Получение конкретной координаты по заданному номеру
     * \see double& operator[](size_t idx)
     */
    double& get(size_t idx);

    /**
     * @brief Получение конкретной координаты по заданному имени оси
     * \see double& operator[](std::string name)
     */
    double& get(std::string name);

    /**
     * @return текущее число координат точки
     */
    size_t size() const;

    /**
     * @brief Устанавливает число координат точки
     * @param num новое число координат
     */
    void setCoordinatesCount(size_t num);

    /**
     * @brief Операторы проверки точек на равенство
     * @param other точка, с которой сравнивается текущая точка
     * @return true, если точки равны, иначе false
     */
    bool operator==(const Point& other) const;

    /**
     * @brief Операторы проверки точек на неравенство
     * @param other точка, с которой сравнивается текущая точка
     * @return true, если точки не равны, иначе false
     */
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

    /**
     * @brief Домножает текущую точку на заданную точку
     * @param other точка, на который домножится текущая точка
     * @return полученная в результате домножения точка
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 2, 3};
     * Point b = {-1, 0.5, 0}
     * a *= b; // a == {-1, 1, 0}
     * \endcode
     */
    Point& operator*=(const Point& other);

    /**
     * @brief Складывает текущую точку с заданной точкой
     * @param other точка, с которой складывается текущая точка
     * @return полученная в результате сложения точка
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 2, 3};
     * Point b = {-1, 0.5, 0}
     * a += b; // a == {0, 2.5, 3}
     * \endcode
     */
    Point& operator+=(const Point& other);

    /**
     * @brief Вычитает из текущей точку заданную точку
     * @param other точка, которая вычитается из текущей точки
     * @return полученная в результате вычитания точка
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 2, 3};
     * Point b = {-1, 0.5, 0}
     * a -= b; // a == {2, 1.5, 3}
     * \endcode
     */
    Point& operator-=(const Point& other);

    /**
     * @return Возвращает текущую точку с инвертированными координатами
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 0, -2};
     * Point b = -a; // b == {-1, 0, 2}
     * \endcode
     */
    Point operator-() const;

    /**
     * @brief Складывает две точки
     * @param other точка, которая прибавляется к текущей
     * @return результат сложения текущей точки с заданной
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 0, -2};
     * Point b = {-1, 1, 2};
     * Point s = a + b; // s == {0, 1, 0}
     * \endcode
     */
    Point operator+(const Point& other);

    /**
     * @brief Находит разницу двух точек
     * @param other точка, которая вычитается из текущей
     * @return результат вычитания текущей точки и заданной
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 0, -2};
     * Point b = {1, 1, -2};
     * Point s = a - b; // s == {0, -1, 0}
     * \endcode
     */
    Point operator-(const Point& other);

    /**
     * @brief Находит произведение двух точек
     * @param other точка, которая умножается на текущую
     * @return результат умножения текущей точки и заданной
     *
     * Пример использования:
     * \code{.cpp}
     * Point a = {1, 0, -2};
     * Point b = {-1, 1, 2};
     * Point s = a * b; // s == {-1, 0, -4}
     * \endcode
     */
    Point operator*(const Point& other);
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


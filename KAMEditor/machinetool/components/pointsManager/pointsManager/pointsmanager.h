#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

#include <vector>
#include <memory>
#include "machinetool/components/pointsManager/point/point.h"

class PointsManager
{
public:
    PointsManager();
    ~PointsManager();

    /**
     * @brief Добавляет точку в список точек
     * @param p указатель на добавляемую точку
     *
     * Пример:
     * \code{.cpp}
     * manager.addPoint( new Point( {0, 1, 2} ) );
     * \endcode
     */
    void addPoint(Point* p);

    /**
     * @brief Удаляет точку из списка точек
     * @param p указатель на удаляемую точку
     */
    void deletePoint(Point* p);

    /**
     * @brief Удаляет точку из списка точек
     * @param p умный указатель на удаляемую точку
     */
    void deletePoint(const std::shared_ptr<Point> &p);

    /**
     * @return текущее количество точек
     */
    size_t pointCount() const;

    /**
     * @brief Задает число координат для каждой точки
     * @param num новое число координат
     */
    void setCoordinatesCount(size_t num);

    /**
     * @brief Возвращает ссылку на точку с заданным номером
     * @param idx номер точки
     * @return ссылка на умный указатель на точку
     * \warning Если заданный номер превышает число точек, бросает исключение out_of_range
     */
    std::shared_ptr<Point>& operator[](size_t idx);

private:
    /// Список всех точек
    std::vector< std::shared_ptr<Point> > m_points;
};

#endif

#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

#include <vector>
#include "point/point.h"


/*!
 * \brief Класс "Менеджер Точек"
 * \brief Данный класс содержит информацию о количестве и параметрах точек позволяет взаимодействовать с ними.
 * \warning Является синглтоном.
 *
 * Способы взаимодействия с классом:
 * 1) Добавление новой точки;
 * 2) Удаление точки;
 * 3) Установка параметров точки;
 * 4) Получение выделенной точки;
 * 5) Получение всех точек;
 */
class PointsManager
{
public:
    //! Возвращает экземпляр класса
    static PointsManager& Instance();

    //! Методы для работы с точками:
    /// \details Добавить точку p в конец вектора точек;
    void addPoint(Point p);

    /// \details Присвоить точке под номером num значение точки p;
    void setPoint(unsigned int num, Point p);

    /// \details Удалить точку под номером num из вектора точек;
    void removePoint(unsigned int num);

    /**
     * Метод для установки выделенной точки;
     * возвращаемое значение true = выделенная точка установлена;
     * возвращаемое значенеи false = выделенная точка не была установлена;
    **/
    bool setSelectedPoint(unsigned int num);

    /// \details Метод для возвращения выделенной точки;
    unsigned int getSelectedPoint();

    /// \details Возвращает все добавленные ранее точки в формате вектора точек;
    std::vector<Point> getPoints();

private:
    //! Ветор точек;
    std::vector<Point> points;

    //! Выделенная точка;
    unsigned int selectedPoint;

    /**
     * \brief Конструктор и деструктор:
     * \warning Конструктор и деструктор недоступны публично
     **/
    PointsManager() {}
    ~PointsManager() {}


    /// \details Запрещение копирования точки
    PointsManager(PointsManager const&);
    PointsManager& operator=(PointsManager const&);
};

#endif

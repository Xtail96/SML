#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

#include <vector>
#include "point.h"

class PointsManager
{
public:
    static PointsManager& Instance();

    // методы для работы с точками
    void addPoint(Point p);
    void setPoint(unsigned int num, Point p);
    void removePoint(unsigned int num);

    bool setSelectedPoint(unsigned int num);
    unsigned int getSelectedPoint();

    std::vector<Point> getPoints();

private:
    // точки
    std::vector<Point> points;

    unsigned int selectedPoint;

    // конструктор и деструктор недоступны публично
    PointsManager() {}
    ~PointsManager() {}

    // запрет копирования
    PointsManager(PointsManager const&);
    PointsManager& operator=(PointsManager const&);
};

#endif

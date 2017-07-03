#include "point.h"

Point::Point(int dimension)
{
    coordinates = std::vector<double>(dimension, 0);
}

Point::Point(std::initializer_list<double> coords) : Point(coords.size())
{
    std::copy(coords.begin(), coords.end(), coordinates.begin());
}

double& Point::operator[](size_t idx)
{
    if (idx < coordinates.size())
        return coordinates[idx];
    else
        throw std::out_of_range("Координаты с номером " + std::to_string(idx) + " не существует.");
}

double& Point::operator[](std::string name)
{
    int idx = axisNames.getKeyByName(name);
    return operator[](idx);
}

bool Point::operator==(const Point &other) const
{
    return (coordinates == other.coordinates);
}

bool Point::operator!=(const Point &other) const
{
    return (coordinates != other.coordinates);
}

Point& Point::operator*=(double x)
{
    for (double& coord : coordinates)
        coord *= x;

    return *this;
}

Point operator*(double x, Point p)
{
    return (p *= x);
}

Point operator*(Point p, double x)
{
    return (p *= x);
}

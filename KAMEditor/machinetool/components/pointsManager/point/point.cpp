#include "point.h"

Point::Point(int dimension)
{
    coordinates = std::vector<double>(dimension, 0);
}

Point::Point(std::initializer_list<double> coords) : Point(coords.size())
{
    std::copy(coords.begin(), coords.end(), coordinates.begin());
}

Point::Point(const std::vector<double> &v) : coordinates(v)
{
}

Point::Point(const Point& other)
{
    coordinates = other.coordinates;
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
    int idx = axisesNames.getKeyByName(name);
    return operator[](idx);
}

double& Point::get(size_t idx)
{
    return operator[](idx);
}

double& Point::get(std::string name)
{
    return operator[](name);
}

size_t Point::size() const
{
    return coordinates.size();
}

void Point::setCoordinatesCount(size_t num)
{
    coordinates.resize(num);
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

Point& Point::operator*=(const Point &other)
{
    assert(coordinates.size() == other.coordinates.size());

    std::transform(coordinates.begin(), coordinates.end(),
                   other.coordinates.begin(),
                   coordinates.begin(),
                   std::multiplies<double>()
                   );

    return *this;
}

Point &Point::operator+=(const Point &other)
{
    assert(coordinates.size() == other.coordinates.size());

    std::transform(coordinates.begin(), coordinates.end(),
                   other.coordinates.begin(),
                   coordinates.begin(),
                   std::plus<double>()
                   );

    return *this;
}

Point &Point::operator-=(const Point &other)
{
    assert(coordinates.size() == other.coordinates.size());

    std::transform(coordinates.begin(), coordinates.end(),
                   other.coordinates.begin(),
                   coordinates.begin(),
                   std::minus<double>()
                   );

    return *this;
}

Point Point::operator-() const
{
    Point p(*this);
    return (-1.0 * p);
}

Point Point::operator+(const Point& other)
{
    Point p(*this);

    return (p += other);
}

Point Point::operator-(const Point &other)
{
    Point p(*this);

    return (p -= other);
}

Point Point::operator*(const Point &other)
{
    Point p(*this);

    return (p *= other);
}

Point operator*(double x, Point p)
{
    return (p *= x);
}

Point operator*(Point p, double x)
{
    return (p *= x);
}

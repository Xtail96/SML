#include "point.h"

Point::Point()
{
    m_coords = {};
}

Point::Point(QMap<QString, double> coords)
{
    m_coords = coords;
}

Point::Point(const Point& other)
{
    m_coords = other.m_coords;
}

Point& Point::operator=(Point other)
{
    m_coords = other.m_coords;
    return *this;
}

void Point::insertAxis(QString axisName, double coord)
{
    m_coords.insert(axisName, coord);
}

QList< QPair<QString, double> > Point::coords()
{
    QStringList axisesUidsSorted = SML_AXES_NAMES.sort(m_coords.keys());

    QList< QPair<QString, double> > result = {};
    for(auto axisUid : axisesUidsSorted)
    {
        result.append(QPair<QString, double>(axisUid, m_coords[axisUid]));
    }
    return result;
}

QMap<QString, double> Point::coordsMap()
{
    return m_coords;
}

double& Point::operator[](QString axisName)
{
    if(!m_coords.contains(axisName)) throw InvalidArgumentException("Axis name " + axisName + " does not exists");
    return m_coords[axisName];
}

double& Point::get(QString axisName)
{
    return operator[](axisName);
}

int Point::size() const
{
    return m_coords.size();
}

bool Point::operator==(const Point &other) const
{
    return (m_coords == other.m_coords);
}

bool Point::operator!=(const Point &other) const
{
    return (m_coords != other.m_coords);
}

Point& Point::operator*=(double x)
{
    for (double& coord : m_coords)
    {
        coord *= x;
    }

    return *this;
}

Point& Point::operator*=(const Point &other)
{
    assert(m_coords.size() == other.m_coords.size());

    std::transform(m_coords.begin(), m_coords.end(),
                   other.m_coords.begin(),
                   m_coords.begin(),
                   std::multiplies<double>()
                   );

    return *this;
}

Point &Point::operator+=(const Point &other)
{
    assert(m_coords.size() == other.m_coords.size());

    std::transform(m_coords.begin(), m_coords.end(),
                   other.m_coords.begin(),
                   m_coords.begin(),
                   std::plus<double>()
                   );

    return *this;
}

Point &Point::operator-=(const Point &other)
{
    assert(m_coords.size() == other.m_coords.size());

    std::transform(m_coords.begin(), m_coords.end(),
                   other.m_coords.begin(),
                   m_coords.begin(),
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

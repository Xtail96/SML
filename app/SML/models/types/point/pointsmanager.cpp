#include "pointsmanager.h"

PointsManager::PointsManager(QObject *parent) :
    QObject(parent)
{
    // резервируем некоторое количество точек наперед, чтобы при добавлении не происходило перераспределение памяти вектора
    m_points.reserve(32);
}

PointsManager::PointsManager(const PointsManager &object) :
    m_points(object.m_points)
{

}

PointsManager::~PointsManager()
{

}

void PointsManager::addPoint(Point *p)
{
    QSharedPointer<Point> ptr(p);
    m_points.push_back(ptr);
    emit pointsUpdated();
}

void PointsManager::deletePoint(Point *p)
{
    deletePoint(QSharedPointer<Point>(p));
    emit pointsUpdated();
}

void PointsManager::deletePoint(const QSharedPointer<Point>& p)
{
    m_points.removeOne(p);// .erase( std::remove(m_points.begin(), m_points.end(), p), m_points.end() );
    emit pointsUpdated();
}

void PointsManager::deletePoint(size_t idx)
{
    QSharedPointer<Point> point = operator [](idx);
    deletePoint(point);
    emit pointsUpdated();
}

void PointsManager::deletePoints(size_t beginIndex, size_t endIndex)
{
    size_t pointsSize = pointCount();
    if((beginIndex <=  pointsSize) && (endIndex <= pointsSize))
    {
        m_points.erase(m_points.begin() + beginIndex, m_points.begin() + endIndex);
    }
    emit pointsUpdated();
}

void PointsManager::updatePoint(QStringList coordinates, unsigned int number)
{
    Point* p = PointsManager::makePoint(coordinates);
    try
    {
        QSharedPointer<Point> originPoint = this->operator [](number);
        unsigned int originPointDimension = originPoint->size();
        unsigned int newPointDimension = p->size();
        unsigned int rangeForUpdate = qMin(originPointDimension, newPointDimension);
        for(unsigned int i = 0; i < rangeForUpdate; i++)
        {
            originPoint->get(i) = p->get(i);
        }
        emit pointsUpdated();
    }
    catch(OutOfRangeException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

size_t PointsManager::pointCount() const
{
    return m_points.size();
}

void PointsManager::setCoordinatesCount(size_t num)
{
    for (auto& point : m_points)
    {
        point->setCoordinatesCount(num);
    }
    emit pointsUpdated();
}

QSharedPointer<Point>& PointsManager::operator[](size_t idx)
{
    if (idx < pointCount())
    {
        return m_points[idx];
    }
    else
    {
        QString message =
                QStringLiteral("Нет точки с номером ") +
                QString::number(idx) +
                QStringLiteral(" (Всего ") +
                QString::number(pointCount()) +
                QStringLiteral(" точек");

        throw OutOfRangeException(message);
    }
}

Point3D PointsManager::getPoint3D(QString idx)
{
    Point3D point3d;
    try
    {
        bool isNumber = true;
        size_t pointNumberValue = idx.toUInt(&isNumber);
        if(isNumber)
        {
            QSharedPointer<Point> pointOriginal = this->operator [](pointNumberValue-1);
            point3d = PointsManager::toPoint3D(pointOriginal);
        }
    }
    catch(...)
    {
        point3d = Point3D(-1, -1, -1);
        throw;
    }
    return point3d;
}

Point3D PointsManager::toPoint3D(QSharedPointer<Point> origin)
{
    Point3D point3d;
    try
    {
        point3d.x = origin->get("X");
        point3d.y = origin->get("Y");
        point3d.z = origin->get("Z");
    }
    catch(...)
    {
        point3d = Point3D(-1, -1, -1);
    }
    return point3d;
}

QList<QStringList> PointsManager::points()
{
    QList<QStringList> points;
    for(auto point : m_points)
    {
        QStringList coordinates;
        unsigned int coordinatesCount = point.data()->size();
        for(unsigned int j = 0; j < coordinatesCount; j++)
        {
            QString coordinate;
            try
            {
                coordinate = QString::number(point.data()->operator [](j));
            }
            catch(OutOfRangeException e)
            {
                QMessageBox(QMessageBox::Warning, "Ошибка", e.message()).exec();
                break;
            }
            coordinates.push_back(coordinate);
        }
        points.push_back(coordinates);

    }
    return points;
}

QStringList PointsManager::point(unsigned int number)
{
    QStringList coordinates;
    try
    {
        QSharedPointer<Point> p = this->operator [](number);
        unsigned int coordinatesCount = p.data()->size();
        for(unsigned int j = 0; j < coordinatesCount; j++)
        {
            QString coordinate;
            coordinate = QString::number(p.data()->operator [](j));
            coordinates.push_back(coordinate);
        }
    }
    catch(OutOfRangeException e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.message()).exec();
    }
    return coordinates;
}

Point *PointsManager::makePoint(QStringList arguments)
{
    QList<double> pointsCoordinates;
    for(auto argument : arguments)
    {
        pointsCoordinates.push_back(argument.toDouble());
    }
    Point* p = new Point(pointsCoordinates.toVector().toStdVector());
    return p;
}


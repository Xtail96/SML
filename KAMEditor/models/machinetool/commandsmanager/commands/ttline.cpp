#include "ttline.h"

TTLine::TTLine(PointsManager *_pointsManager, QString _destinationPointNumber, bool _airPassageIsNeed, QString _dz, QString _v) :
    pointsManager(_pointsManager), destinationPointNumber(_destinationPointNumber), airPassageIsNeed(_airPassageIsNeed), dz(_dz), v(_v)
{

}

TTLine::~TTLine()
{

}

byte_array TTLine::getDataForMachineTool() const
{

}

void TTLine::draw(OGLWidget *w) const
{
    if(!airPassageIsNeed)
    {
        w->drawTTLine(destinationPoint(w));
    }
    else
    {
        bool isNumber = true;
        double dzValue = dz.toDouble(&isNumber);
        if(isNumber)
        {
            w->drawAirPassage(destinationPoint(w), dzValue, 1);
        }
    }
}

Point3D TTLine::destinationPoint(OGLWidget *w) const
{
    Point3D destination;
    try
    {
        bool isNumber = true;
        unsigned int destinationPointNumberValue = destinationPointNumber.toUInt(&isNumber);
        if(isNumber)
        {
            std::shared_ptr<Point> destinationPoint = pointsManager->operator [](destinationPointNumberValue-1);
            destination.x = destinationPoint->get("X");
            destination.y = destinationPoint->get("Y");
            destination.z = destinationPoint->get("Z");
        }
        else
        {
            destination = w->getCurrentPoint();
        }
    }
    catch(...)
    {
        destination = w->getCurrentPoint();
    }
    return destination;
}

size_t TTLine::getId() const
{
    return id;
}

std::string TTLine::getName() const
{
    return name;
}

QStringList TTLine::getArguments() const
{
    QStringList arguments =
    {
        destinationPointNumber,
        QString::number(airPassageIsNeed),
        dz,
        v
    };
    return arguments;
}

QString TTLine::getArgumentsString() const
{
    QString qArgumentsString = "Точка назначения = " + destinationPointNumber +
            ",  Воздушный переход = " + QString::number(airPassageIsNeed) + ", dz = " + dz + ", v = " + v;
    return qArgumentsString;
}

QColor TTLine::getColor() const
{
    return color;
}

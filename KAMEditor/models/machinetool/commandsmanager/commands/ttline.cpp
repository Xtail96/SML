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
    if(isArgumentsCorrect())
    {
        if(!airPassageIsNeed)
        {
            w->drawTTLine(destinationPoint(w), v.toDouble());
        }
        else
        {
            w->drawAirPassage(destinationPoint(w), dz.toDouble(), v.toDouble());
        }
    }
}

Point3D TTLine::destinationPoint(OGLWidget *w) const
{
    Point3D destination;
    try
    {
        bool isNumber = true;
        size_t destinationPointNumberValue = destinationPointNumber.toUInt(&isNumber);
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

bool TTLine::isArgumentsCorrect() const
{
    bool isCorrect = true;

    QList<bool> isNumberFlags =
    {
        true,
        true,
        true
    };

    size_t tmp1;
    tmp1 = destinationPointNumber.toUInt(&isNumberFlags[0]);

    double tmp2;
    tmp2 = dz.toDouble(&isNumberFlags[1]);
    tmp2 = v.toDouble(&isNumberFlags[2]);

    for(auto flag : isNumberFlags)
    {
        if(flag == false)
        {
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

size_t TTLine::getId() const
{
    return id;
}

QString TTLine::getName() const
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

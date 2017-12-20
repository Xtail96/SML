#include "smlttline.h"

SMLTTLine::SMLTTLine(PointsManager *_pointsManager, QString _destinationPointNumber, bool _airPassageIsNeed, QString _dz, QString _v) :
    pointsManager(_pointsManager), destinationPointNumber(_destinationPointNumber), airPassageIsNeed(_airPassageIsNeed), dz(_dz), v(_v)
{

}

SMLTTLine::~SMLTTLine()
{

}

byte_array SMLTTLine::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void SMLTTLine::draw(OGLWidget *w) const
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

Point3D SMLTTLine::destinationPoint(OGLWidget *w) const
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

bool SMLTTLine::isArgumentsCorrect() const
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

size_t SMLTTLine::getId() const
{
    return id;
}

QString SMLTTLine::getName() const
{
    return name;
}

QStringList SMLTTLine::getArguments() const
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

void SMLTTLine::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 4)
    {
       destinationPointNumber = arguments[0];
       airPassageIsNeed = arguments[1].toInt();
       dz = arguments[2];
       v = arguments[3];
    }
}

QString SMLTTLine::getArgumentsString() const
{
    QString qArgumentsString = "Точка назначения = " + destinationPointNumber +
            ",  Воздушный переход = " + QString::number(airPassageIsNeed) + ", dz = " + dz + ", v = " + v;
    return qArgumentsString;
}

QColor SMLTTLine::getColor() const
{
    return color;
}

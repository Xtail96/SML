#include "smltttarc.h"

SMLTTTArc::SMLTTTArc(PointsManager *_pointsManager, QString _middlePointNumber, QString _endPointNumber, QString _v) :
    pointsManager(_pointsManager),
    middlePointNumber(_middlePointNumber),
    endPointNumber(_endPointNumber),
    v(_v)
{

}

SMLTTTArc::~SMLTTTArc()
{

}

byte_array SMLTTTArc::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void SMLTTTArc::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        w->drawTTTArc(pointsManager->getPoint3D(middlePointNumber), pointsManager->getPoint3D(endPointNumber));
    }
}

size_t SMLTTTArc::getId() const
{
    return id;
}

QString SMLTTTArc::getName() const
{
    return name;
}

QStringList SMLTTTArc::getArguments() const
{
    QStringList arguments =
    {
        middlePointNumber,
        endPointNumber,
        v
    };
    return arguments;
}

void SMLTTTArc::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 3)
    {
        middlePointNumber = arguments[0];
        endPointNumber = arguments[1];
        v = arguments[2];
    }
}

QString SMLTTTArc::getArgumentsString() const
{
    QString qArgumentsString = "Точка назначения = " + endPointNumber +
            ",  Точка на середине = " + middlePointNumber + ", v = " + v;
    return qArgumentsString;
}

QColor SMLTTTArc::getColor() const
{
    return color;
}

bool SMLTTTArc::isArgumentsCorrect() const
{
    bool isCorrect = true;

    QList<bool> isNumberFlags =
    {
        true,
        true,
        true
    };

    size_t tmp1;
    tmp1 = middlePointNumber.toUInt(&isNumberFlags[0]);
    tmp1 = endPointNumber.toUInt(&isNumberFlags[1]);

    double tmp2;
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

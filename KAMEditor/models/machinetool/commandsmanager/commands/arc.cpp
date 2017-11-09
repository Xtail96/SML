#include "arc.h"

CArc::CArc(QString R, QString Al, QString Fi, QString v) :
    R(R), Al(Al), Fi(Fi), v(v)
{
}

byte_array CArc::getDataForMachineTool() const
{

}

void CArc::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        w->drawArc(R.toDouble(), Al.toDouble(), Fi.toDouble(), v.toDouble());
    }
}

size_t CArc::getId() const
{
    return id;
}

QString CArc::getName() const
{
    return name;
}

QStringList CArc::getArguments() const
{
    QStringList arguments =
    {
        R,
        Al,
        Fi,
        v
    };
    return arguments;
}

void CArc::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 4)
    {
        R = arguments[0];
        Al = arguments[1];
        Fi = arguments[2];
        v = arguments[3];
    }
}

QString CArc::getArgumentsString() const
{
    QString qArgumentsString = "R = " + R + ", Al = " + Al + ", Fi = " + Fi + ", v = " + v;
    return qArgumentsString;
}

bool CArc::isArgumentsCorrect() const
{
    bool isCorrect = true;

    QList<bool> isNumberFlags =
    {
        true,
        true,
        true,
        true
    };

    double tmp;
    tmp = R.toDouble(&isNumberFlags[0]);
    tmp = Al.toDouble(&isNumberFlags[1]);
    tmp = Fi.toDouble(&isNumberFlags[2]);
    tmp = v.toDouble(&isNumberFlags[3]);

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

QColor CArc::getColor() const
{
    return color;
}

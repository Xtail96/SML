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
    w->drawArc(R.toDouble(), Al.toDouble(), Fi.toDouble(), v.toDouble());
}

size_t CArc::getId() const
{
    return id;
}

std::string CArc::getName() const
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

QString CArc::getArgumentsString() const
{
    QString qArgumentsString = "R = " + R + ", Al = " + Al + ", Fi = " + Fi + ", v = " + v;
    return qArgumentsString;
}

QColor CArc::getColor() const
{
    return color;
}

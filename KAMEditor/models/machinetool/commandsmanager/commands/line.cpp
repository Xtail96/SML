#include "line.h"

Line::Line(QString dx, QString dy, QString dz, QString v) :
    dx(dx), dy(dy), dz(dz), v(v)
{

}

byte_array Line::getDataForMachineTool() const
{

}

void Line::draw(OGLWidget *w) const
{
    w->drawLine(dx.toDouble(), dy.toDouble(), dz.toDouble(), v.toDouble());
}

size_t Line::getId() const
{
    return id;
}

std::string Line::getName() const
{
    return name;
}

QStringList Line::getArguments() const
{
    QStringList arguments =
    {
        dx,
        dy,
        dz,
        v
    };
    return arguments;
}

QString Line::getArgumentsString() const
{
    QString qArgumentsString = "dx = " + dx + ", dy = " + dy + ", dz = " + dz + ", v = " + v;
    return qArgumentsString;
}

QColor Line::getColor() const
{
    return color;
}

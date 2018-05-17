#include "line.h"

Line::Line(QString dx, QString dy, QString dz, QString v) :
    dx(dx), dy(dy), dz(dz), v(v)
{

}

byte_array Line::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void Line::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        w->drawLine(dx.toDouble(), dy.toDouble(), dz.toDouble(), v.toDouble());
    }
}

size_t Line::getId() const
{
    return id;
}

QString Line::getName() const
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

void Line::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 4)
    {
        dx = arguments[0];
        dy = arguments[1];
        dz = arguments[2];
        v = arguments[3];
    }
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

bool Line::isArgumentsCorrect() const
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
    tmp = dx.toDouble(&isNumberFlags[0]);
    tmp = dy.toDouble(&isNumberFlags[1]);
    tmp = dz.toDouble(&isNumberFlags[2]);
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

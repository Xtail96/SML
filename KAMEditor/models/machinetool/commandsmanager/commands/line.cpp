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
    QList<bool> isNumberFlags=
    {
        true,
        true,
        true,
        true
    };
    double dxValue = dx.toDouble(&isNumberFlags[0]);
    double dyValue = dy.toDouble(&isNumberFlags[1]);
    double dzValue = dz.toDouble(&isNumberFlags[2]);
    double velocityValue = v.toDouble(&isNumberFlags[3]);

    bool isCorrect = true;
    for(auto flag : isNumberFlags)
    {
        if(flag == false)
        {
            isCorrect = false;
            break;
        }
    }

    if(isCorrect)
    {
        w->drawLine(dxValue, dyValue, dzValue, velocityValue);
    }
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

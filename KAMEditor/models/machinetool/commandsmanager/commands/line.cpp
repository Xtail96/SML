#include "line.h"

Line::Line(double dx, double dy, double dz, double v) :
    dx(dx), dy(dy), dz(dz), v(v)
{

}

byte_array Line::getDataForMachineTool() const
{

}

void Line::draw(OGLWidget *w) const
{
    w->drawLine(dx, dy, dz, v);
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
        QString::number(dx),
        QString::number(dy),
        QString::number(dz),
        QString::number(v)
    };
    return arguments;
}

QString Line::getArgumentsString() const
{
    QString qArgumentsString = "dx = " + QString::number(dx) + ", dy = " + QString::number(dy) + ", dz = " + QString::number(dz) + ", v = " + QString::number(v);
    return qArgumentsString;
}

QColor Line::getColor() const
{
    return color;
}


void OGLWidget::drawLine(double dx, double dy, double dz, double v)
{
    glBegin(GL_LINES);

    glVertex3f(currentPoint.x, currentPoint.y, currentPoint.z);

    double newX = currentPoint.x + dx;
    double newY = currentPoint.y + dy;
    double newZ = currentPoint.z + dz;

    glVertex3f(newX, newY, newZ);

    glEnd();

    Point3D destinaton(newX, newY, newZ);
    updateOffsets(destinaton);
    updateCurrentPoint(destinaton);
}

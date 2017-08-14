#include "line.h"

Line::Line(double dx, double dy, double dz, double v) :
    dx(dx), dy(dy), dz(dz), v(v)
{

}

byte_array Line::getDataForMachineTool() const
{

}

void Line::draw(OGLWidget *w, Point3D src) const
{
    w->drawLine(dx, dy, dz, v, src);
}

Point3D Line::returnDestinationPoint(Point3D sourcePoint) const
{
    Point3D destinationPoint(dx + sourcePoint.x, dy + sourcePoint.y, dz + sourcePoint.z);
    return destinationPoint;
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
        "dx = " + QString::number(dx),
        "dy = " + QString::number(dy),
        "dz = " + QString::number(dz),
        "v = " + QString::number(v)
    };
    return arguments;
}

QColor Line::getColor() const
{
    return color;
}


void OGLWidget::drawLine(double dx, double dy, double dz, double v, Point3D src)
{
    glBegin(GL_LINES);

    glVertex3f(src.x, src.y, src.z);
    glVertex3f(src.x + dx, src.y + dy, src.z + dz);

    glEnd();
}

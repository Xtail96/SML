#include "line.h"

Line::Line(double dx, double dy, double dz, double v) :
    dx(dx), dy(dy), dz(dz), v(v)
{

}

byte_array Line::getDataForMachineTool() const
{

}

void Line::draw(OGLWidget *w, SourcePoint src) const
{
    w->drawLine(dx, dy, dz, v, src);
}

size_t Line::getId() const
{
    return id;
}

std::string Line::getName() const
{
    return name;
}

QString Line::getArguments() const
{
    std::string arguments = "dx = " + std::to_string(dx) + ", dy = " + std::to_string(dy) + ", dz = " + std::to_string(dz) + ", v = " + std::to_string(v);
    return QString::fromStdString(arguments);
}

QColor Line::getColor() const
{
    return color;
}


void OGLWidget::drawLine(double dx, double dy, double dz, double v, SourcePoint src)
{
    glBegin(GL_LINES);

    glVertex3f(src.x, src.y, src.z);
    glVertex3f(src.x + dx, src.y + dy, src.z + dz);

    glEnd();
}

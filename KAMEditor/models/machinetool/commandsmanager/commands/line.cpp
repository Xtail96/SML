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

}

std::string Line::getName() const
{
    return "Линия";
}

QString Line::getArguments() const
{
    return "";
}

QColor Line::getColor() const
{
    return QColor("#333");
}

void OGLWidget::drawLine(double dx, double dy, double dz, double v)
{
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);

    glVertex3f(0, 0, 0);
    glVertex3f(dx, dy, dz);

    glEnd();
}

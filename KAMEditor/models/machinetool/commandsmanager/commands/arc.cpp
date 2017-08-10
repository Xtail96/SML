#include "arc.h"

CArc::CArc(double R, double Al, double Fi, double v) :
    R(R), Al(Al), Fi(Fi), v(v)
{
}

byte_array CArc::getDataForMachineTool() const
{

}

void CArc::draw(OGLWidget *w, SourcePoint sourcePoint) const
{
    w->drawArc(R, Al, Fi, v);
}

size_t CArc::getId() const
{
    return id;
}

std::string CArc::getName() const
{
    return "Дуга";
}

QString CArc::getArguments() const
{
    std::string arguments = "R = " + std::to_string(R) + ", Al = " + std::to_string(Al) + ", Fi = " + std::to_string(Fi) + ", v = " + std::to_string(v);
    return QString::fromStdString(arguments);
}

QColor CArc::getColor() const
{
    return color;
}

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v)
{
    double endAngle = startAngle + arcAngle;
    double angleIncrement = 0.01;

    double x, y;

    glBegin(GL_LINE_STRIP);

    for (double theta = startAngle; theta < endAngle; theta += angleIncrement)
    {
        x = radius * cos(theta);
        y = radius * sin(theta);

        glVertex2f(x, y);
    }

    glEnd();
}

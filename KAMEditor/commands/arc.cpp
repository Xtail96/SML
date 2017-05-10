#include "arc.h"

CArc::CArc(double R, double Al, double Fi, double v) :
    R(R), Al(Al), Fi(Fi), v(v)
{

}

void CArc::send() const
{

}

void CArc::draw(OGLWidget *w) const
{
    w->drawArc(R, Al, Fi, v);
}

QString CArc::getName() const
{
    return QString("Дуга");
}

QString CArc::getArguments() const
{
    return "Not implemented yet";
}

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v)
{
    double endAngle = startAngle + arcAngle;
    double angleIncrement = 0.01;

    double x, y;

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);

    for (double theta = startAngle; theta < endAngle; theta += angleIncrement)
    {
        x = radius * cos(theta);
        y = radius * sin(theta);

        glVertex2f(x, y);
    }

    glEnd();
}

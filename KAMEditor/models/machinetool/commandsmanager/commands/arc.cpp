#include "arc.h"

CArc::CArc(double R, double Al, double Fi, double v) :
    R(R), Al((M_PI/180)*Al), Fi((M_PI/180)*Fi), v(v)
{
}

byte_array CArc::getDataForMachineTool() const
{

}

void CArc::draw(OGLWidget *w) const
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

QStringList CArc::getArguments() const
{
    QStringList arguments =
    {
        QString::number(R),
        QString::number(Al),
        QString::number(Fi),
        QString::number(v)
    };
    return arguments;
}

QString CArc::getArgumentsString() const
{
    QString qArgumentsString = "R = " + QString::number(R) + ", Al = " + QString::number(Al) + ", Fi = " + QString::number(Fi) + ", v = " + QString::number(v);
    return qArgumentsString;
}

QColor CArc::getColor() const
{
    return color;
}

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v)
{
    double angleIncrement = 0.01;

    double x, y;

    Point3D center;
    center.x = currentPoint.x /*+ cos(startAngle)*/;
    center.y = currentPoint.y /*- sin(startAngle)*/ - radius;

    glBegin(GL_LINE_STRIP);

    for (double theta = 0; theta < arcAngle; theta += angleIncrement)
    {
        x = center.x + radius * cos(theta);
        y = center.y + radius * sin(theta);

        glVertex2f(x, y);

        Point3D newVertex(x, y, currentPoint.z);
        updateOffsets(newVertex);
        updateCurrentPoint(newVertex);
    }

    glEnd();
}

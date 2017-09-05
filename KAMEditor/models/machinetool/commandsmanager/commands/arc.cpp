#include "arc.h"

CArc::CArc(double R, double Al, double Fi, double v) :
    R(R), Al(Al), Fi(Fi), v(v)
{
}

byte_array CArc::getDataForMachineTool() const
{

}

void CArc::draw(OGLWidget *w, Point3D sourcePoint) const
{
    w->drawArc(R, Al, Fi, v, sourcePoint);
}

Point3D CArc::returnDestinationPoint(Point3D sourcePoint) const
{
    return sourcePoint;
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

Point3D CArc::getCenter() const
{
    return center;
}

void CArc::setCenter(const Point3D &value)
{
    center = value;
}

QColor CArc::getColor() const
{
    return color;
}

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v, Point3D src)
{
    startAngle = (M_PI/180)*startAngle;
    arcAngle = (M_PI/180)*arcAngle;

    double angleIncrement = 0.01;

    double x, y;

    Point3D center;
    center.x = src.x /*+ cos(startAngle)*/;
    center.y = src.y /*- sin(startAngle)*/ - radius;

    glBegin(GL_LINE_STRIP);

    for (double theta = 0; theta < arcAngle; theta += angleIncrement)
    {
        x = center.x + radius * cos(theta);
        y = center.y + radius * sin(theta);

        glVertex2f(x, y);
    }

    glEnd();
}

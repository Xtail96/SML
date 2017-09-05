#include "arc.h"

CArc::CArc(double R, double Al, double Fi, double v) :
    R(R), Al((M_PI/180)*Al), Fi((M_PI/180)*Fi), v(v)
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
    Point3D center;
    center.x = sourcePoint.x;
    center.y = sourcePoint.y - R;

    Point3D destinationPoint = sourcePoint;
    destinationPoint.x = center.x + R * cos(Fi);
    destinationPoint.y = center.y + R * sin(Fi);

    return destinationPoint;
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

void OGLWidget::drawArc(double radius, double startAngle, double arcAngle, double v, Point3D src)
{
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

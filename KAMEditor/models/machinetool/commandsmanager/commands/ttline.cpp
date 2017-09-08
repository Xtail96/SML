#include "ttline.h"

TTLine::TTLine(std::shared_ptr<Point> _destinationPoint, unsigned int _destinationPointNumber, bool _airPassageIsNeed, double _dz, double _v) :
    destinationPoint(_destinationPoint), destinationPointNumber(_destinationPointNumber), airPassageIsNeed(_airPassageIsNeed), dz(_dz), v(_v)
{

}

TTLine::~TTLine()
{

}

byte_array TTLine::getDataForMachineTool() const
{

}

void TTLine::draw(OGLWidget *w, Point3D sourcePoint) const
{
    if(!airPassageIsNeed)
    {
        w->drawTTLine(returnDestinationPoint(sourcePoint), 1, sourcePoint);
    }
    else
    {
        w->drawAirPassage(returnDestinationPoint(sourcePoint), dz, 1, sourcePoint);
    }
}

Point3D TTLine::returnDestinationPoint(Point3D sourcePoint) const
{
    Point3D destination = sourcePoint;
    destination.x = destinationPoint->get("X");
    destination.y = destinationPoint->get("Y");
    destination.z = destinationPoint->get("Z");
    return destination;
}

size_t TTLine::getId() const
{
    return id;
}

std::string TTLine::getName() const
{
    return name;
}

QStringList TTLine::getArguments() const
{
    QStringList arguments =
    {
        QString::number(destinationPointNumber),
        QString::number(airPassageIsNeed),
        QString::number(dz),
        QString::number(v)
    };
    return arguments;
}

QString TTLine::getArgumentsString() const
{
    QString qArgumentsString = "Точка назначения = " + QString::number(destinationPointNumber) +
            ",  Воздушный переход = " + QString::number(airPassageIsNeed) + ", dz = " + QString::number(dz) + ", v = " + QString::number(v);
    return qArgumentsString;
}

QColor TTLine::getColor() const
{
    return color;
}

void OGLWidget::drawTTLine(Point3D dest, double v, Point3D src)
{
    glBegin(GL_LINES);

    glVertex3f(src.x, src.y, src.z);

    glVertex3f(dest.x, dest.y, dest.z);

    updateOffsets(dest);

    glEnd();
}

void OGLWidget::drawAirPassage(Point3D dest, double dz, double v, Point3D src)
{

    double newZ = src.z + dz;
    Point3D firstVertex = Point3D(src.x, src.y, newZ);
    Point3D secondVertex = Point3D(dest.x, dest.y, newZ);

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1111);

    glBegin(GL_LINES);

    glVertex3f(src.x, src.y, src.z);

    glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);

    glEnd();

    glBegin(GL_LINES);

    glVertex3f(firstVertex.x, firstVertex.y, firstVertex.z);

    glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);

    glEnd();

    glBegin(GL_LINES);

    glVertex3f(secondVertex.x, secondVertex.y, secondVertex.z);

    glVertex3f(dest.x, dest.y, dest.z);

    glEnd();

    updateOffsets(firstVertex);

    updateOffsets(secondVertex);

    updateOffsets(dest);
}

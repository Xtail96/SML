#include "pause.h"

Pause::Pause(size_t _length) :
    length(_length)
{

}

Pause::~Pause()
{

}

byte_array Pause::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void Pause::draw(OGLWidget *w, Point3D sourcePoint) const
{
    QString text = "Пауза";
    w->qglColor(Qt::red);
    w->renderText(sourcePoint.x, sourcePoint.y, sourcePoint.z, text);
}

Point3D Pause::returnDestinationPoint(Point3D sourcePoint) const
{
    return sourcePoint;
}

std::string Pause::getName() const
{
    return name;
}

size_t Pause::getId() const
{
    return id;
}

QStringList Pause::getArguments() const
{
    QStringList arguments =
    {
        QString::number(length)
    };
    return arguments;
}

QColor Pause::getColor() const
{
    return color;
}

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

void Pause::draw(OGLWidget *w) const
{

}

std::string Pause::getName() const
{
    return name;
}

size_t Pause::getId() const
{
    return id;
}

QString Pause::getArguments() const
{
    return QString::number(length) + " секунд";
}

QColor Pause::getColor() const
{
    return color;
}

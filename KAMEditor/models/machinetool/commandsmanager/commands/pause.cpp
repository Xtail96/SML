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
    QString text = "Пауза";
    w->qglColor(Qt::red);
    w->renderText(w->getCurrentPoint().x, w->getCurrentPoint().y, w->getCurrentPoint().z, text);
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

QString Pause::getArgumentsString() const
{
    return QString::number(length) + " секунд";
}

QColor Pause::getColor() const
{
    return color;
}

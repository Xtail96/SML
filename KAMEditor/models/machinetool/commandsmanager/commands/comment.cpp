#include "comment.h"

Comment::Comment(std::string _comment) :
    comment(_comment)
{

}

Comment::~Comment()
{

}

byte_array Comment::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void Comment::draw(OGLWidget *w, Point3D sourcePoint) const
{

}

Point3D Comment::returnDestinationPoint(Point3D sourcePoint) const
{
    return sourcePoint;
}

std::string Comment::getName() const
{
    return "***";
}

size_t Comment::getId() const
{
    return id;
}

QStringList Comment::getArguments() const
{
    QStringList arguments =
    {
        QString::fromStdString(comment)
    };
    return arguments;
}

QString Comment::getArgumentsString() const
{
    return QString::fromStdString(comment);
}

QColor Comment::getColor() const
{
    return color;
}

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

void Comment::draw(OGLWidget *w, SourcePoint sourcePoint) const
{

}

SourcePoint Comment::returnDestinationPoint(SourcePoint sourcePoint) const
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

QString Comment::getArguments() const
{
    return QString::fromStdString(comment);
}

QColor Comment::getColor() const
{
    return color;
}

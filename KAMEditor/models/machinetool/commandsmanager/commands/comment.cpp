#include "comment.h"

Comment::Comment(QString _comment) :
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

void Comment::draw(OGLWidget *w) const
{

}

QString Comment::getName() const
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
        comment
    };
    return arguments;
}

QString Comment::getArgumentsString() const
{
    return comment;
}

QColor Comment::getColor() const
{
    return color;
}

bool Comment::isArgumentsCorrect() const
{
    return true;
}

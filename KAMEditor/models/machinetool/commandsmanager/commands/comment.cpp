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

void Comment::draw(OGLWidget *w) const
{

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

bool Comment::isArgumentsCorrect() const
{
    return true;
}

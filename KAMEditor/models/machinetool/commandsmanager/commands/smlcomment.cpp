#include "smlcomment.h"

SMLComment::SMLComment(QString _comment) :
    comment(_comment)
{

}

SMLComment::~SMLComment()
{

}

QString SMLComment::getName() const
{
    return "***";
}

size_t SMLComment::getId() const
{
    return id;
}

QStringList SMLComment::getArguments() const
{
    QStringList arguments =
    {
        comment
    };
    return arguments;
}

void SMLComment::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 1)
    {
        comment = arguments[0];
    }
}

QString SMLComment::getArgumentsString() const
{
    return comment;
}

QColor SMLComment::getColor() const
{
    return color;
}

bool SMLComment::isArgumentsCorrect() const
{
    return true;
}

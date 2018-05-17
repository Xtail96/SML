#include "smlpause.h"

SMLPause::SMLPause(QString _length)
{
    try
    {
        int _lengthValue = _length.toInt();
        if(_lengthValue >= 0)
        {
            length = _length;
        }
        else
        {
            length = QString::number(0);
        }
    }
    catch(...)
    {
        length = QString::number(0);
        QMessageBox(QMessageBox::Warning, "Ошибка", "Неизвестный тип аршумента").exec();
    }
}

SMLPause::~SMLPause()
{

}

byte_array SMLPause::getDataForMachineTool() const
{
    byte_array data;
    return data;
}

void SMLPause::draw(OGLWidget *w) const
{
    if(isArgumentsCorrect())
    {
        QString text = "Пауза";
        w->qglColor(Qt::red);
        w->renderText(w->getCurrentPoint().x, w->getCurrentPoint().y, w->getCurrentPoint().z, text);
    }
}

QString SMLPause::getName() const
{
    return name;
}

size_t SMLPause::getId() const
{
    return id;
}

QStringList SMLPause::getArguments() const
{
    QStringList arguments =
    {
        length
    };
    return arguments;
}

void SMLPause::setArguments(const QStringList arguments)
{
    if(arguments.length() >= 1)
    {
        length = arguments[0];
    }
}

QString SMLPause::getArgumentsString() const
{
    return length + " секунд";
}

QColor SMLPause::getColor() const
{
    return color;
}

bool SMLPause::isArgumentsCorrect() const
{
    bool isCorrect = true;
    size_t tmp;
    tmp = length.toUInt(&isCorrect);
    return isCorrect;
}


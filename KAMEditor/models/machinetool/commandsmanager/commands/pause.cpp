#include "pause.h"

Pause::Pause(QString _length)
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
    if(isArgumentsCorrect())
    {
        QString text = "Пауза";
        w->qglColor(Qt::red);
        w->renderText(w->getCurrentPoint().x, w->getCurrentPoint().y, w->getCurrentPoint().z, text);
    }
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
        length
    };
    return arguments;
}

QString Pause::getArgumentsString() const
{
    return length + " секунд";
}

QColor Pause::getColor() const
{
    return color;
}

bool Pause::isArgumentsCorrect() const
{
    bool isCorrect = true;
    size_t tmp;
    tmp = length.toUInt(&isCorrect);
    return isCorrect;
}


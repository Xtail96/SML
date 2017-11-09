#include "smlvariable.h"

SMLVariable::SMLVariable(QString _key, QString _value) :
    key(_key), value(_value)
{
    if(!isArgumentsCorrect())
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", "Неизвестный тип значения переменной!\nЗначение переменной будет установлено в 0").exec();
        value = QString::number(0);
    }
}

SMLVariable::~SMLVariable()
{

}

void SMLVariable::draw(OGLWidget *w) const
{

}

QString SMLVariable::getName() const
{
    return name;
}

size_t SMLVariable::getId() const
{
    return id;
}

QStringList SMLVariable::getArguments() const
{
    QStringList arguments =
    {
        key,
        value
    };
    return arguments;
}

void SMLVariable::setArguments(const QStringList arguments)
{
    if(arguments.size() >= 2)
    {
        key = arguments[0];
        value = arguments[1];
    }
}

QString SMLVariable::getArgumentsString() const
{
    QString argumentsString = key + " = " + value;
    return argumentsString;
}

QColor SMLVariable::getColor() const
{
    return color;
}

bool SMLVariable::isArgumentsCorrect() const
{
    bool isCorrect = true;
    double tmp;
    tmp = value.toDouble(&isCorrect);
    return isCorrect;
}

byte_array SMLVariable::getDataForMachineTool() const
{
    byte_array ignored;
    return ignored;
}

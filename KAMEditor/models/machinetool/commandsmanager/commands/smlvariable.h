#ifndef SMLVARIABLE_H
#define SMLVARIABLE_H

#include "smlcommand.h"

class SMLVariable : public SMLCommand
{
private:
    size_t id = CMD_VARIABLE;
    const QString name = "Переменная";
    QString key;
    QString value;
    QColor color = SmlColors::blue();
public:
    SMLVariable(QString _key, QString _value);

    ~SMLVariable();

    /**
     * @return имя текущей команды
     */
    QString getName() const override;

    /**
     * @return Id команды
     */
    size_t getId() const override;

    /**
     * @return строковое представление каждого из аргументов текущей команды
     */
    QStringList getArguments() const override;

    void setArguments(const QStringList arguments) override;

    /**
     * @return подробное строковое представление аргументов текущей команды
     */
    QString getArgumentsString() const override;

    /**
     * @return цвет текущей команды
     */
    QColor getColor() const override;

    /**
     * @brief Проверяет корректность аргументов
     * @return true, если все аргументы корректны, false - иначе
     */
    bool isArgumentsCorrect() const override;

};

#endif // SMLVARIABLE_H

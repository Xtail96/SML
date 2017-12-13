#ifndef COMMENT_H
#define COMMENT_H

#include "models/machinetool/commandsmanager/commands/smlcommand.h"

class SMLComment : public SMLCommand
{
private:
    size_t id = CMD_COMMENT;
    const QString name = "Комментарий";
    QString comment;
    QColor color = QColor(SmlColors::lightGray());
public:
    SMLComment(QString _comment = "");
    ~SMLComment();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    byte_array getDataForMachineTool() const override;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    void draw(OGLWidget* w) const override;

    /**
     * @return имя текущей команды
     */
    QString getName() const override;

    /**
     * @return ID команды
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

    QColor getColor() const override;

    bool isArgumentsCorrect() const override;
};

#endif // COMMENT_H

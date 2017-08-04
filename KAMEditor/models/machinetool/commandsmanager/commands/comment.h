#ifndef COMMENT_H
#define COMMENT_H

#include "models/machinetool/commandsmanager/commands/command.h"
#include "models/machinetool/machinetool.h"

class Comment : public Command
{
private:
    size_t id = CMD_COMMENT;
    const std::string name = "Комментарий";
    std::string comment;
    QColor color = QColor(SmlColors::lightGray());
public:
    Comment(std::string _comment = "");
    virtual ~Comment();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    virtual byte_array getDataForMachineTool() const;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    virtual void draw(OGLWidget* w) const;

    /**
     * @return имя текущей команды
     */
    virtual std::string getName() const;

    /**
     * @return ID команды
     */
    virtual size_t getId() const;

    /**
     * @return строковое представление аргументов текущей команды
     */
    virtual QString getArguments() const;

    virtual QColor getColor() const;
};

#endif // COMMENT_H

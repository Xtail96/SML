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
    ~Comment();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    byte_array getDataForMachineTool() const override;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    void draw(OGLWidget* w, Point3D sourcePoint = Point3D()) const override;

    Point3D returnDestinationPoint(Point3D sourcePoint = Point3D()) const override;

    /**
     * @return имя текущей команды
     */
    std::string getName() const override;

    /**
     * @return ID команды
     */
    size_t getId() const override;

    /**
     * @return строковое представление каждого из аргументов текущей команды
     */
    QStringList getArguments() const override;

    /**
     * @return подробное строковое представление аргументов текущей команды
     */
    QString getArgumentsString() const override;

    QColor getColor() const override;
};

#endif // COMMENT_H

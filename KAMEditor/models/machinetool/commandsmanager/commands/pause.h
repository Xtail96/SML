#ifndef PAUSE_H
#define PAUSE_H

#include "models/machinetool/commandsmanager/commands/command.h"

class Pause : public Command
{
private:
    size_t id = CMD_PAUSE;
    const std::string name = "Пауза";
    QString length;
    QColor color = QColor(SmlColors::red());

    bool isArgumentsCorrect() const;
public:
    Pause(QString _length);
    ~Pause();

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

#endif // PAUSE_H

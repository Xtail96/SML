#ifndef PAUSE_H
#define PAUSE_H

#include "models/machinetool/commandsmanager/commands/command.h"
#include "models/machinetool/machinetool.h"

class Pause : public Command
{
private:
    size_t id = CMD_PAUSE;
    const std::string name = "Пауза";
    size_t length;
    QColor color = QColor(SmlColors::red());
public:
    Pause(size_t _length);
    virtual ~Pause();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    virtual byte_array getDataForMachineTool() const;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    virtual void draw(OGLWidget* w, SourcePoint sourcePoint = SourcePoint()) const;

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

#endif // PAUSE_H

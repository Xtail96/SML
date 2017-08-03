#ifndef SWITCHON_H
#define SWITCHON_H

#include "models/machinetool/commandsmanager/commands/command.h"
#include "models/structs.h"
#include "models/machinetool/machinetool.h"

class SwitchOn : public Command
{
    size_t id = 2;
    const std::string name = "Включить";
    MachineTool* machineTool;
    std::vector<std::string> arguments;
public:
    SwitchOn(MachineTool* _machineTool, std::vector<std::string> _arguments);
    ~SwitchOn();

    /**
     * @brief Отправляет текущую команду на станок
     */
    virtual void send() const override;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    virtual void draw(OGLWidget* w) const override;

    /**
     * @return имя текущей команды
     */
    virtual std::string getName() const override;

    /**
     * @return ID команды
     */
    virtual size_t getId() const override;

    /**
     * @return строковое представление аргументов текущей команды
     */
    virtual QString getArguments() const override;
};

#endif // SWITCHON_H

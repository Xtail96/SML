#ifndef SWITCHOFF_H
#define SWITCHOFF_H

#include "models/machinetool/commandsmanager/commands/command.h"
#include "models/machinetool/machinetool.h"

class SwitchOff : public Command
{
private:
    size_t id = CMD_SWITCH_OFF;
    const std::string name = "Выключить";
    MachineTool* machineTool;
    std::string deviceName;
    std::string parametrs;
    QColor color = QColor(SmlColors::green());
public:
    SwitchOff(MachineTool* _machineTool, std::string _deviceName, std::string _parametrs = 0);
    ~SwitchOff();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    virtual byte_array getDataForMachineTool() const override;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    virtual void draw(OGLWidget* w, double red = 0, double green = 0, double blue = 0) const override;

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

    QColor getColor() const override;
};

#endif // SWITCHOFF_H

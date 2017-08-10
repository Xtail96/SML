#ifndef SWITCHON_H
#define SWITCHON_H

#include "models/machinetool/commandsmanager/commands/command.h"
#include "models/machinetool/machinetool.h"

class SwitchOn : public Command
{
    size_t id = CMD_SWITCH_ON;
    const std::string name = "Включить";
    MachineTool* machineTool;
    std::string deviceName;
    std::string parametrs;
    QColor color = QColor(SmlColors::red());
public:
    SwitchOn(MachineTool* _machineTool, std::string _deviceName, std::string _parametrs = 0);
    ~SwitchOn();

    /**
     * @brief Получает данные, которые нужно отправить на станок, чтобы выполнить команду
     */
    byte_array getDataForMachineTool() const override;

    /**
     * @brief Отвечает за графическое отображение команды
     * @param w виджет, куда происходит отрисовка
     */
    void draw(OGLWidget* w, SourcePoint sourcePoint = SourcePoint()) const override;
    SourcePoint returnDestinationPoint(SourcePoint sourcePoint = SourcePoint()) const override;

    /**
     * @return имя текущей команды
     */
    std::string getName() const override;

    /**
     * @return ID команды
     */
    size_t getId() const override;

    /**
     * @return строковое представление аргументов текущей команды
     */
    QString getArguments() const override;

    QColor getColor() const override;
};

#endif // SWITCHON_H

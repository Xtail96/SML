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
     * @return строковое представление аргументов текущей команды
     */
    QString getArguments() const override;

    QColor getColor() const override;
};

#endif // SWITCHOFF_H

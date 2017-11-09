#ifndef SWITCHON_H
#define SWITCHON_H

#include "models/machinetool/commandsmanager/commands/command.h"

class SwitchOn : public Command
{
    size_t id = CMD_SWITCH_ON;
    const QString name = "Включить";

    DevicesManager* devicesManager;

    QString deviceName;
    QString parametrs;
    QColor color = QColor(SmlColors::red());
public:
    SwitchOn(DevicesManager* _devicesManager, QString _deviceName, QString _parametrs = "");
    ~SwitchOn();

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

#endif // SWITCHON_H

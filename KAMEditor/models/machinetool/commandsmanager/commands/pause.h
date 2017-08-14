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
    ~Pause();

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
    QStringList getArguments() const override;

    QColor getColor() const override;
};

#endif // PAUSE_H

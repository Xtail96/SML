#ifndef ARC_H
#define ARC_H

#include <cmath>

#include "command.h"

class CArc : public Command
{
public:
    CArc(double R, double Al, double Fi, double v = 1);

    virtual byte_array getDataForMachineTool() const override;
    void draw(OGLWidget* w, double red = 0, double green = 0, double blue = 0) const override;

    size_t getId() const override;
    std::string getName() const override;
    QString getArguments() const override;

    virtual QColor getColor() const override;

private:
    size_t id = CMD_ARC;

    std::string name = "Дуга";

    // радиус дуги
    double R;

    // начальный угол
    double Al;

    // величина поворота
    double Fi;

    // скорость
    double v;

    QColor color = SmlColors::gray();
};

#endif // ARC_H

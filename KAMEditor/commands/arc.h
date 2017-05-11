#ifndef ARC_H
#define ARC_H

#include <cmath>

#include "command.h"

class CArc : public Command
{
public:
    CArc(double R, double Al, double Fi, double v = 1);

    void send() const override;
    void draw(OGLWidget* w) const override;

    QString getName() const override;
    QString getArguments() const override;

private:
    // радиус дуги
    double R;
    // начальный угол
    double Al;
    // величина поворота
    double Fi;
    // скорость
    double v;
};

#endif // ARC_H

#ifndef ARC_H
#define ARC_H

#include "command.h"

class Arc : public Command
{
public:
    Arc(double R, double Al, double Fi, double v = 1);

    void send() const override;
    void draw() const override;

    QString getName() const override;

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

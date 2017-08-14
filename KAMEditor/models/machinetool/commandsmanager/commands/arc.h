#ifndef ARC_H
#define ARC_H

#include <cmath>

#include "command.h"

class CArc : public Command
{
public:
    CArc(double R, double Al, double Fi, double v = 1);

    byte_array getDataForMachineTool() const override;
    void draw(OGLWidget* w, Point3D sourcePoint = Point3D()) const override;
    Point3D returnDestinationPoint(Point3D sourcePoint = Point3D()) const override;

    size_t getId() const override;
    std::string getName() const override;
    QStringList getArguments() const override;

    QColor getColor() const override;

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

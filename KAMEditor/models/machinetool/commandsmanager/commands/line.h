#ifndef LINE_H
#define LINE_H

#include "command.h"

class Line : public Command
{
public:
    Line(double dx, double dy, double dz, double v = 1);

    byte_array getDataForMachineTool() const override;
    void draw(OGLWidget* w, Point3D sourcePoint = Point3D()) const override;
    Point3D returnDestinationPoint(Point3D sourcePoint = Point3D()) const override;

    size_t getId() const override;
    std::string getName() const override;
    QString getArguments() const override;

    QColor getColor() const override;

private:
    size_t id = CMD_LINE;
    std::string name = "Линия";
    double dx, dy, dz;
    double v;
    QColor color = SmlColors::gray();
};

#endif // LINE_H

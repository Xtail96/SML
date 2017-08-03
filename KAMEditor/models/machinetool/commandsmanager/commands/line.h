#ifndef LINE_H
#define LINE_H

#include "command.h"

class Line : public Command
{
public:
    Line(double dx, double dy, double dz, double v = 1);

    byte_array getDataForMachineTool() const override;
    void draw(OGLWidget* w) const override;

    size_t getId() const override;
    std::string getName() const override;
    QString getArguments() const override;

    virtual QColor getColor() const override;

private:
    double dx, dy, dz;
    double v;
};

#endif // LINE_H

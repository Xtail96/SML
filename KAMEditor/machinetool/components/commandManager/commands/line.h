#ifndef LINE_H
#define LINE_H

#include "command.h"

class Line : public Command
{
public:
    Line(double dx, double dy, double dz, double v = 1);

    void send() const override;
    void draw(OGLWidget* w) const override;

    std::string getName() const override;
    QString getArguments() const override;

private:
    double dx, dy, dz;
    double v;
};

#endif // LINE_H

#ifndef GCODESMANAGER_H
#define GCODESMANAGER_H

#include <QString>
#include <QDebug>

#include "./gpr/parser.h"

class GCodesManager
{
protected:
public:
    GCodesManager();
    ~GCodesManager();

    void updateGCodesProgram(const std::string &data);

    //gpr::gcode_program gcodes() const;
};

#endif // GCODESMANAGER_H

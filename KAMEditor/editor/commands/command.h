#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include "../../gui/oglwidget.h"

class Command
{
public:
    virtual void send() const = 0;
    virtual void draw(OGLWidget* w) const = 0;

    virtual QString getName() const = 0;

    // скорее всего, временные методы, будет переделано при рефакторинге
    virtual std::string getEditorColor() const { return "#000000"; }
    virtual QString getArguments() const = 0;
    int getId() const { return id; }

private:
    int id;
};

#endif // COMMAND_H

#ifndef PROGRAMVISUALIZEWINDOWCONTROLLER_H
#define PROGRAMVISUALIZEWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class ProgramVisualizeWindowController : public MainWindowController
{
    Q_OBJECT
public:
    explicit ProgramVisualizeWindowController(QObject *parent = nullptr);

signals:

public slots:

private:
    CommandsInterpreter* commandsInterpreter;

    bool run;
    unsigned int minimalGridSize = 1;

    void setup();
};

#endif // PROGRAMVISUALIZEWINDOWCONTROLLER_H

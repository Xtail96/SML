#ifndef PROGRAMVISUALIZEWINDOWCONTROLLER_H
#define PROGRAMVISUALIZEWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class ProgramVisualizeWindowController : public QObject
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
};

#endif // PROGRAMVISUALIZEWINDOWCONTROLLER_H

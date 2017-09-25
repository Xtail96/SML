#ifndef PROGRAMVISUALIZEWINDOWBRIDGE_H
#define PROGRAMVISUALIZEWINDOWBRIDGE_H

#include <QTableWidgetItem>
#include <QMessageBox>

#include "models/structs.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class ProgramVisualizeWindowBridge
{
public:
    ProgramVisualizeWindowBridge();

    QStringList commandsHeaders();
    QStringList commandsNumbers(unsigned int commandsCount);

    QList<QTableWidgetItem*> commandsNames(CommandsInterpreter* interpreter);
    QList<QTableWidgetItem*> commandsArguments(CommandsInterpreter* interpreter);
};

#endif // PROGRAMVISUALIZEWINDOWBRIDGE_H

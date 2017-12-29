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

    QList<QTableWidgetItem*> commandsNames(std::vector<std::shared_ptr<SMLCommand> > commands);
    QList<QTableWidgetItem*> commandsArguments(std::vector<std::shared_ptr<SMLCommand> > commands);
};

#endif // PROGRAMVISUALIZEWINDOWBRIDGE_H

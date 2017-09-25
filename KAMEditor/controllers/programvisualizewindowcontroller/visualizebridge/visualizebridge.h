#ifndef VISUALIZEBRIDGE_H
#define VISUALIZEBRIDGE_H

#include <QTableWidgetItem>
#include <QMessageBox>

#include "models/structs.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class VisualizeBridge
{
public:
    VisualizeBridge();

    QStringList commandsHeaders();
    QStringList commandsNumbers(unsigned int commandsCount);

    QList<QTableWidgetItem*> commandsNames(CommandsInterpreter* interpreter);
    QList<QTableWidgetItem*> commandsArguments(CommandsInterpreter* interpreter);
};

#endif // VISUALIZEBRIDGE_H

#ifndef VISUALIZEBRIDGE_H
#define VISUALIZEBRIDGE_H

#include <QTableWidgetItem>

#include "models/structs.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class VisualizeBridge
{
public:
    VisualizeBridge();

    QStringList commandsHeaders();
    QStringList commandsNumbers(unsigned int commandsCount);

    QList<QTableWidgetItem*> commands(CommandsInterpreter* interpreter);
};

#endif // VISUALIZEBRIDGE_H

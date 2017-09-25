#include "programvisualizewindowcontroller.h"

ProgramVisualizeWindowController::ProgramVisualizeWindowController(QObject *parent) : MainWindowController(parent)
{
    setup();
}

void ProgramVisualizeWindowController::setup()
{
    commandsInterpreter = machineTool->getCommandsInterpreter();
}

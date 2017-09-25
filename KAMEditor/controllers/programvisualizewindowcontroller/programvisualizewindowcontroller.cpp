#include "programvisualizewindowcontroller.h"

ProgramVisualizeWindowController::ProgramVisualizeWindowController(MainWindowController *_mainController, QObject *parent) : QObject(parent)
{
    setup(_mainController);
}

ProgramVisualizeWindowController::~ProgramVisualizeWindowController()
{
    delete visualizeBridge;
}

CommandsInterpreter *ProgramVisualizeWindowController::getCommandsInterpreter() const
{
    return commandsInterpreter;
}

void ProgramVisualizeWindowController::setCommandsInterpreter(CommandsInterpreter *value)
{
    commandsInterpreter = value;
}

PointsManager *ProgramVisualizeWindowController::getPointsManager() const
{
    return pointsManager;
}

void ProgramVisualizeWindowController::setPointsManager(PointsManager *value)
{
    pointsManager = value;
}

void ProgramVisualizeWindowController::setup(MainWindowController* mainController)
{
    commandsInterpreter = mainController->machineTool->getCommandsInterpreter();

    pointsManager = mainController->machineTool->getPointsManager();

    visualizeBridge = new VisualizeBridge();
}

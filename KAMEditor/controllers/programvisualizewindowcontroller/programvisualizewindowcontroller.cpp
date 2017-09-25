#include "programvisualizewindowcontroller.h"

ProgramVisualizeWindowController::ProgramVisualizeWindowController(MainWindowController *_mainController, QObject *parent) : QObject(parent)
{
    setup(_mainController);
    emit ready();
}

ProgramVisualizeWindowController::~ProgramVisualizeWindowController()
{
    delete programVisualizeBridge;
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

double ProgramVisualizeWindowController::getGridMaximalAccuracy() const
{
    return gridMaximalAccuracy;
}

void ProgramVisualizeWindowController::setup(MainWindowController* mainController)
{
    commandsInterpreter = mainController->machineTool->getCommandsInterpreter();

    pointsManager = mainController->machineTool->getPointsManager();

    programVisualizeBridge = new VisualizeBridge();

    SettingsManager settingsManager;
    try
    {
        gridMaximalAccuracy = settingsManager.get("Visualisation", "GridMaximalAccuracy").toDouble();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

QStringList ProgramVisualizeWindowController::getCommandsHeaders()
{
    return programVisualizeBridge->commandsHeaders();
}

QStringList ProgramVisualizeWindowController::getCommandsNumbers()
{
    return programVisualizeBridge->commandsNumbers(commandsInterpreter->commandsCount());
}

QList<QTableWidgetItem *> ProgramVisualizeWindowController::getCommandsNames()
{
    return programVisualizeBridge->commandsNames(commandsInterpreter);
}

QList<QTableWidgetItem *> ProgramVisualizeWindowController::getCommandsArguments()
{
    return programVisualizeBridge->commandsArguments(commandsInterpreter);
}

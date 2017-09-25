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

std::vector<std::shared_ptr<Command> > ProgramVisualizeWindowController::getCommands()
{
    std::vector< std::shared_ptr<Command> > commands;

    size_t commandsCount = commandsInterpreter->commandsCount();

    for(unsigned int i = 0; i < commandsCount; i++)
    {
        try
        {
            std::shared_ptr<Command> command = commandsInterpreter->operator [](i);
            commands.push_back(command);
        }
        catch(std::out_of_range e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
            break;
        }
    }

    return commands;
}

std::vector<std::shared_ptr<Point3D> > ProgramVisualizeWindowController::get3DPoints()
{
    std::vector< std::shared_ptr<Point3D> > points;

    size_t pointsCount = pointsManager->pointCount();

    for(unsigned int i = 0; i < pointsCount; i++)
    {
        try
        {
            std::shared_ptr<Point> originPoint = pointsManager->operator [](i);
            Point3D* point = new Point3D(originPoint->get("X"), originPoint->get("Y"), originPoint->get("Z"));
            points.push_back(std::shared_ptr<Point3D>(point));
        }
        catch(std::out_of_range e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
            break;
        }
    }

    return points;
}

double ProgramVisualizeWindowController::getGridMaximalAccuracy() const
{
    return gridMaximalAccuracy;
}

void ProgramVisualizeWindowController::setup(MainWindowController* mainController)
{
    commandsInterpreter = mainController->machineTool->getCommandsInterpreter();

    pointsManager = mainController->machineTool->getPointsManager();

    programVisualizeBridge = new ProgramVisualizeWindowBridge();

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

#include "programvisualizewindowcontroller.h"

ProgramVisualizeWindowController::ProgramVisualizeWindowController(MainWindowController *_mainWindowController, QObject *parent) : QObject(parent)
{
    setup(_mainWindowController);
    emit ready();
}

ProgramVisualizeWindowController::~ProgramVisualizeWindowController()
{
    delete programVisualizeBridge;
}

std::vector<std::shared_ptr<SMLCommand> > ProgramVisualizeWindowController::getCommands()
{
    return interpretedCommands;
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

void ProgramVisualizeWindowController::setup(MainWindowController* mainWindowController)
{
    programVisualizeBridge = new ProgramVisualizeWindowBridge();

    interpretedCommands = mainWindowController->interpretCommands();

    pointsManager = mainWindowController->machineTool->getPointsManager();

    gCodesData = mainWindowController->getGCodesProgram();

    SettingsManager settingsManager;
    try
    {
        gridMaximalAccuracy = settingsManager.get("Visualisation", "GridMaximalAccuracy").toDouble();
        double xSize = settingsManager.get("Table_Size", "SizeX").toDouble();
        double ySize = settingsManager.get("Table_Size", "SizeY").toDouble();
        double zSize = settingsManager.get("Table_Size", "SizeZ").toDouble();
        tableSize = Point3D(xSize, ySize, zSize);
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
    return programVisualizeBridge->commandsNumbers(interpretedCommands.size());
}

QList<QTableWidgetItem *> ProgramVisualizeWindowController::getCommandsNames()
{
    return programVisualizeBridge->commandsNames(interpretedCommands);
}

QList<QTableWidgetItem *> ProgramVisualizeWindowController::getCommandsArguments()
{
    return programVisualizeBridge->commandsArguments(interpretedCommands);
}

QString ProgramVisualizeWindowController::getGCodesData() const
{
    return gCodesData;
}

Point3D ProgramVisualizeWindowController::getTableSize() const
{
    return tableSize;
}

Point3D ProgramVisualizeWindowController::getZeroCoordinates() const
{
    return zeroCoordinates;
}

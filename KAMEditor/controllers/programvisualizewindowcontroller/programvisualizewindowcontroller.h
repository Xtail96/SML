#ifndef PROGRAMVISUALIZEWINDOWCONTROLLER_H
#define PROGRAMVISUALIZEWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"
#include "controllers/programvisualizewindowcontroller/programvisualizewindowbridge/programvisualizewindowbridge.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class MainWindowController;

class ProgramVisualizeWindowController : public QObject
{
    Q_OBJECT
public:
    explicit ProgramVisualizeWindowController(MainWindowController* _mainWindowController, QObject *parent = nullptr);
    ~ProgramVisualizeWindowController();

    std::vector< std::shared_ptr<SMLCommand> > getCommands();

    std::vector< std::shared_ptr<Point3D> > get3DPoints();

    double getGridMaximalAccuracy() const;

    QStringList getCommandsHeaders();

    QStringList getCommandsNumbers();

    QList<QTableWidgetItem *> getCommandsNames();
    QList<QTableWidgetItem *> getCommandsArguments();

signals:
    void ready();

public slots:

private:
    ProgramVisualizeWindowBridge* programVisualizeBridge;

    std::vector< std::shared_ptr<SMLCommand> > interpretedCommands;

    PointsManager* pointsManager;

    bool run;
    unsigned int minimalGridSize = 1;
    double gridMaximalAccuracy;

    void setup(MainWindowController *mainWindowController);

    friend class MainWindowController;
};

#endif // PROGRAMVISUALIZEWINDOWCONTROLLER_H

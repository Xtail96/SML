#ifndef PROGRAMVISUALIZEWINDOWCONTROLLER_H
#define PROGRAMVISUALIZEWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"
#include "controllers/programvisualizewindowcontroller/visualizebridge/visualizebridge.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

class MainWindowController;

class ProgramVisualizeWindowController : public QObject
{
    Q_OBJECT
public:
    explicit ProgramVisualizeWindowController(MainWindowController* _mainController, QObject *parent = nullptr);
    ~ProgramVisualizeWindowController();



    CommandsInterpreter *getCommandsInterpreter() const;
    void setCommandsInterpreter(CommandsInterpreter *value);

    PointsManager *getPointsManager() const;
    void setPointsManager(PointsManager *value);

    double getGridMaximalAccuracy() const;

signals:

public slots:

private:
    VisualizeBridge* visualizeBridge;

    CommandsInterpreter* commandsInterpreter;

    PointsManager* pointsManager;

    bool run;
    unsigned int minimalGridSize = 1;
    double gridMaximalAccuracy;

    void setup(MainWindowController *mainController);

    friend class MainWindowController;
};

#endif // PROGRAMVISUALIZEWINDOWCONTROLLER_H

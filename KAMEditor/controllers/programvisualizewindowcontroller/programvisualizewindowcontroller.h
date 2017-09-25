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
    explicit ProgramVisualizeWindowController(MainWindowController* _mainController, QObject *parent = nullptr);
    ~ProgramVisualizeWindowController();



    CommandsInterpreter *getCommandsInterpreter() const;
    void setCommandsInterpreter(CommandsInterpreter *value);

    PointsManager *getPointsManager() const;
    void setPointsManager(PointsManager *value);

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

    CommandsInterpreter* commandsInterpreter;

    PointsManager* pointsManager;

    bool run;
    unsigned int minimalGridSize = 1;
    double gridMaximalAccuracy;

    void setup(MainWindowController *mainController);

    friend class MainWindowController;
};

#endif // PROGRAMVISUALIZEWINDOWCONTROLLER_H

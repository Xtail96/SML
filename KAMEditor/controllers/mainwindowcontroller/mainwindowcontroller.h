#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

#include "models/structs.h"
#include "models/machinetool/machinetool.h"
#include "controllers/mainwindowcontroller/mainbridge/mainbridge.h"

class MainWindowController : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowController(QObject *parent = nullptr);
    ~MainWindowController();
protected:
    MachineTool* machineTool;

signals:
    void machineToolSettingsIsLoaded();

public slots:
};

#endif // MAINWINDOWCONTROLLER_H

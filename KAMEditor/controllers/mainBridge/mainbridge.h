#ifndef MAINBRIDGE_H
#define MAINBRIDGE_H

#include "models/structs.h"
#include "models/machinetool/machinetool.h"


class MainBridge : public QObject
{
    Q_OBJECT
signals:
    void machineToolSettingsIsLoaded();
public:
    MainBridge();
    ~MainBridge();
private:
    MachineTool* machineTool;
};

#endif // MAINBRIDGE_H

#ifndef MAINWINDOWBRIDGE_H
#define MAINWINDOWBRIDGE_H

#include <QStringList>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>

#include "models/devicesmanager/device/device.h"
#include "models/pointsmanager/pointsmanager.h"

class MainWindowBridge
{
public:
    MainWindowBridge();
    ~MainWindowBridge();

    static QList<QStringList> points(PointsManager* pointsManager);
    static QStringList point(PointsManager* pointsManager, unsigned int number);

    static Point *makePoint(QStringList arguments);

    //QList<QTreeWidgetItem *> commands(CommandsManager* commandsManager);

    //std::vector< std::shared_ptr<SMLCommand> > getAllCommandsInVector(CommandsManager* commandsManager);

private:
};

#endif // MAINBWINDOWRIDGE_H

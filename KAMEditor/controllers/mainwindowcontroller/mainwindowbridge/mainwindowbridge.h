#ifndef MAINWINDOWBRIDGE_H
#define MAINWINDOWBRIDGE_H

#include <QStringList>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>

#include "models/machinetool/machinetool.h"

class MainWindowBridge
{
public:
    MainWindowBridge();
    ~MainWindowBridge();

    QStringList sensorsNames(std::vector< std::shared_ptr<Sensor> > sensors);
    QStringList sensorsParametrsNames();
    QList<QStringList> sensorsSettings(std::vector< std::shared_ptr<Sensor> > sensors);
    QList<QColor> sensorsLeds(std::vector< std::shared_ptr<Sensor> > sensors);

    QStringList devicesNames(std::vector< std::shared_ptr<Device> > devices);
    QStringList devicesParametrsNames();
    QList<QStringList> devicesSettings(std::vector< std::shared_ptr<Device> > devices);
    QStringList onScreenDevicesNames(std::vector< std::shared_ptr<Device> > devices);
    QList<bool> onScreenDevicesStates(std::vector< std::shared_ptr<Device> > devices);

    QStringList axisesNames(std::vector< std::shared_ptr<Axis> > axises);
    QStringList axisesParametrsNames();
    QList<QStringList> axisesSettings(std::vector< std::shared_ptr<Axis> > axises);

    QList<QStringList> points(PointsManager* pointsManager);
    QStringList point(PointsManager* pointsManager, unsigned int number);

    Point *makePoint(QStringList arguments);

    QList<QTreeWidgetItem *> commands(CommandsManager* commandsManager);

    std::vector< std::shared_ptr<SMLCommand> > getAllCommandsInVector(CommandsManager* commandsManager);

private:
};

#endif // MAINBWINDOWRIDGE_H
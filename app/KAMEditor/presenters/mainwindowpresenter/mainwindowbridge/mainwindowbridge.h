#ifndef MAINWINDOWBRIDGE_H
#define MAINWINDOWBRIDGE_H

#include <QStringList>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>

#include "models/sensorsmanager/sensor/sensor.h"
#include "models/devicesmanager/device/device.h"
#include "models/pointsmanager/pointsmanager.h"

class MainWindowBridge
{
public:
    MainWindowBridge();
    ~MainWindowBridge();

    static QStringList sensorsNames(std::vector< std::shared_ptr<Sensor> > sensors);
    static QStringList sensorsParametrsNames();
    static QList<QStringList> sensorsSettings(std::vector< std::shared_ptr<Sensor> > sensors);
    static QList<QColor> sensorsLeds(std::vector< std::shared_ptr<Sensor> > sensors);

    static QStringList devicesNames(std::vector< std::shared_ptr<Device> > devices);
    static QStringList devicesParametrsNames();
    static QList<QStringList> devicesSettings(std::vector< std::shared_ptr<Device> > devices);
    static QStringList onScreenDevicesNames(std::vector< std::shared_ptr<Device> > devices);
    static QList<bool> onScreenDevicesStates(std::vector< std::shared_ptr<Device> > devices);

    //QStringList axisesNames(std::vector< std::shared_ptr<Axis> > axises);
    static QStringList axisesParametrsNames();
    //QList<QStringList> axisesSettings(std::vector< std::shared_ptr<Axis> > axises);

    static QList<QStringList> points(PointsManager* pointsManager);
    static QStringList point(PointsManager* pointsManager, unsigned int number);

    static Point *makePoint(QStringList arguments);

    //QList<QTreeWidgetItem *> commands(CommandsManager* commandsManager);

    //std::vector< std::shared_ptr<SMLCommand> > getAllCommandsInVector(CommandsManager* commandsManager);

private:
};

#endif // MAINBWINDOWRIDGE_H

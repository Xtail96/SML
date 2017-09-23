#ifndef MAINBRIDGE_H
#define MAINBRIDGE_H

#include <QStringList>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>

#include "models/structs.h"
#include "models/machinetool/machinetool.h"
#include "models/machinetool/commandsmanager/commands/commands.h"

class MainBridge
{
public:
    MainBridge();
    ~MainBridge();

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

    std::shared_ptr<Command> makeCommand(int id, QStringList arguments, MachineTool* machineTool);
    std::shared_ptr<Command> makeSwitchOnCommand(QStringList arguments, DevicesManager *deviceManager);
    std::shared_ptr<Command> makeSwitchOffCommand(QStringList arguments, DevicesManager *deviceManager);
    std::shared_ptr<Command> makeCommentCommand(QStringList arguments);
    std::shared_ptr<Command> makePauseCommand(QStringList arguments);
    std::shared_ptr<Command> makeLineCommand(QStringList arguments);
    std::shared_ptr<Command> makeTTLineCommand(QStringList arguments, PointsManager *pointsManager);

    QList<QTreeWidgetItem *> commands(CommandsManager* commandsManager);

private:
};

#endif // MAINBRIDGE_H

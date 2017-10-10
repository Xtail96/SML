#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMessageBox>
#include <QFileDialog>

#include "models/machinetool/commandsmanager/commands/commandsbuilder.h"
#include "models/machinetool/pointsmanager/point/pointsbuilder.h"

class FileManager
{
public:
    FileManager(CommandsManager* cm, PointsManager* pm, size_t _axisesCount);

    static QString createFile(QString name, const QString path);
    void newFile();
    void openFile();
    void openFile(QString path);
    void saveFile();
    void saveFileAs();
    void addFile();

private:
    CommandsManager* cmd_mgr;
    PointsManager* pnt_mgr;
    size_t axisesCount;

    QString filepath;
    //bool changed;

    void saveCommands(QFile& f);
    void savePoints(QFile& f);

    void resetContainers();
    void resetCommands();
    void resetPoints();

    QString readFileInfo(QString path);

    void transferToSML(QString content);
    void transferToSMLCommands(QStringList commandsStrings);
    void transferToSMLPoints(QStringList pointsStrings);

    std::shared_ptr<Command> makeCommand(QString commandString);
    Point *makePoint(QString pointString);

    QString makeCommandString(std::shared_ptr<Command> commmand);
    QString makePointString(std::shared_ptr<Point> point);

};

#endif // FILEMANAGER_H

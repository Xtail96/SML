#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMessageBox>
#include <QFileDialog>

#include "models/machinetool/commandsmanager/commands/commandsbuilder.h"
#include "models/machinetool/pointsmanager/point/pointsbuilder.h"

class FileManager
{
public:
    FileManager(CommandsManager* cm, PointsManager* pm);

    QFile createFile();
    void saveFile();
    void openFile();

private:
    CommandsManager* cmd_mgr;
    PointsManager* pnt_mgr;

    QString filepath;
    //bool changed;

    void saveCommands(QFile& f);
    void savePoints(QFile& f);

    void readFileInfo(QString path);

    void transferToSML(QString content);
    void transferToSMLCommands(QStringList commandsStrings);
    void transferToSMLPoints(QStringList pointsStrings);

    std::shared_ptr<Command> makeCommand(QString commandString);
    Point *makePoint(QString pointString);

    QString makeCommandsString(std::shared_ptr<Command> cmd);

};

#endif // FILEMANAGER_H

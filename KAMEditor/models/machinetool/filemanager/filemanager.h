#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMessageBox>
#include "../commandsmanager/commandsmanager.h"
#include "../pointsmanager/pointsmanager.h"

class FileManager
{
public:
    FileManager(CommandsManager* cm, PointsManager* pm);

    QFile createFile();
    void saveFile();

private:
    CommandsManager* cmd_mgr;
    PointsManager* pnt_mgr;

    QString filepath;
    bool changed;

    void saveCommands(QFile& f);
    void savePoints(QFile& f);
};

#endif // FILEMANAGER_H

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "../commandsmanager/commandsmanager.h"
#include "../pointsmanager/pointsmanager.h"

class FileManager
{
public:
    FileManager();

private:
    CommandsManager cmd_mgr;
    PointsManager* p_mgr;
};

#endif // FILEMANAGER_H

#ifndef COMMANDSBUILDER_H
#define COMMANDSBUILDER_H

#include "models/machinetool/commandsmanager/commands/smlcommands.h"

class SMLCommandsBuilder
{
public:
    SMLCommandsBuilder();

    static std::shared_ptr<SMLCommand> buildCommand(int id, QStringList arguments,
                                                 PointsManager* pointsManager,
                                                 DevicesManager* devicesManager);

    static std::shared_ptr<SMLCommand> buildArcCommand(QStringList arguments);
    static std::shared_ptr<SMLCommand> buildCommentCommand(QStringList arguments);
    static std::shared_ptr<SMLCommand> buildLine(QStringList arguments);
    static std::shared_ptr<SMLCommand> buildPauseCommand(QStringList arguments);
    static std::shared_ptr<SMLCommand> buildTTLineCommand(QStringList arguments, PointsManager* pointsManager);
    static std::shared_ptr<SMLCommand> buildSwitchOnCommand(QStringList arguments, DevicesManager* devicesManager);
    static std::shared_ptr<SMLCommand> buildSwitchOffCommand(QStringList arguments, DevicesManager* devicesManager);
    static std::shared_ptr<SMLCommand> buildSMLVariableCommand(QStringList arguments);
    static std::shared_ptr<SMLCommand> buildSMLTTTArcCommand(QStringList arguments, PointsManager *pointsManager);
};

#endif // COMMANDSBUILDER_H

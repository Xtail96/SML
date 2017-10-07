#ifndef COMMANDSBUILDER_H
#define COMMANDSBUILDER_H

#include "models/machinetool/commandsmanager/commands/commands.h"

class CommandsBuilder
{
public:
    CommandsBuilder();

    static std::shared_ptr<Command> buildCommand(int id, QStringList arguments);

    static std::shared_ptr<Command> buildArcCommand(QStringList arguments);
    static std::shared_ptr<Command> buildCommentCommand(QStringList arguments);
    static std::shared_ptr<Command> buildLine(QStringList arguments);
    static std::shared_ptr<Command> buildPauseCommand(QStringList arguments);
};

#endif // COMMANDSBUILDER_H

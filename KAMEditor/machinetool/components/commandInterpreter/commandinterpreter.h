#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <thread>
#include <stack>
#include <string>
#include <map>

#include "machinetool/components/commandManager/commands/command.h"


class CommandInterpreter
{
public:
    CommandInterpreter();
    ~CommandInterpreter();
private:
    std::vector<Command*> commands;
};

#endif // COMMANDINTERPRETER_H

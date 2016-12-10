#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <functional>
#include <vector>
#include <map>

#include "command.h"
#include "machinetool.h"

typedef std::vector<std::string> arguments;
typedef std::function<void(arguments)> commandHandler;

void CMD_ARC_HANDLER(arguments args);


static std::map<COMMAND, commandHandler> commandHandlerMap = {
    { CMD_ARC, CMD_ARC_HANDLER }
//    {},
};


#endif // COMMANDHANDLER_H

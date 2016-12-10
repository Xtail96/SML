#include "commandinterpreter.h"

CommandInterpreter::CommandInterpreter()
{
    running = false;

    currentCommand = 0;
}

CommandInterpreter::~CommandInterpreter()
{
}

CommandInterpreter& CommandInterpreter::Instance()
{
    static CommandInterpreter m;
    return m;
}

void CommandInterpreter::addCommand(Command cmd)
{
    commands.push_back(cmd);
}

void CommandInterpreter::Step()
{
    if (currentCommand < commands.size())
    {
        Command cmd = commands[currentCommand];

        commandHandlerMap[cmd.id](cmd.args);

        switch (cmd.id) {
        case CMD_CALL:
            callStack.push(currentCommand + 1);
            currentCommand = functionsMap[ cmd.args[0] ];
            break;

        case CMD_RETURN:
            currentCommand = callStack.top();
            callStack.pop();
            break;

        case CMD_FOR:
            loopStack.push(std::make_pair(currentCommand, std::stoi(cmd.args[0]) ));
            currentCommand++;
            break;

        case CMD_ENDFOR:
            if (loopStack.top().second > 0)
            {
                loopStack.top().second--;
                currentCommand = loopStack.top().first + 1;
            }
            else
            {
                loopStack.pop();
                currentCommand++;
            }

            break;

        case CMD_LABEL:
            labelsMap.insert( std::make_pair(cmd.args[0], currentCommand) );
            break;

        case CMD_GOTO:
            currentCommand = labelsMap[ cmd.args[0] ];
            break;

        case CMD_END:
            Stop();
            break;

        default:
            currentCommand++;
            break;
        }
    }
}

void CommandInterpreter::Run()
{
    running = true;

    t = std::thread(&_Run, this);
    t.detach();
}

void CommandInterpreter::_Run()
{
    while (running && ( commands[currentCommand].id != CMD_END ))
        Step();
}

void CommandInterpreter::Stop()
{
    running = false;
}

#include "commandinterpreter.h"

CommandInterpreter::CommandInterpreter()
{
    running = false;
    selectedCommand = 0;

    currentCommand = 0;
    selectedCommandEditSignal = false;
}

CommandInterpreter::~CommandInterpreter()
{
}

CommandInterpreter& CommandInterpreter::Instance()
{
    static CommandInterpreter m;
    return m;
}

void CommandInterpreter::addCommand(Command cmd, unsigned int selected_command)
{
    std::vector<Command>::iterator commandInsertIt;
    commandInsertIt = commands.begin() + selected_command;
    commands.insert(commandInsertIt, 1, cmd);
}

unsigned int CommandInterpreter::getSelectedCommand()
{
    return selectedCommand;
}

void CommandInterpreter::setSelectedCommand(unsigned int number)
{
    selectedCommand = number;
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

    //t = std::thread(&_Run, this);
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
std::vector <Command> CommandInterpreter::getCommands()
{
    return commands;
}
void CommandInterpreter::deleteSelectedCommands(unsigned int numbers)
{
    if (numbers < commands.size())
        commands.erase(commands.begin() + numbers);
}
void CommandInterpreter::setSelectedCommandEditSignal(bool value)
{
    selectedCommandEditSignal = value;
}
bool CommandInterpreter::getSelectedCommandEditSignal()
{
    return selectedCommandEditSignal;
}

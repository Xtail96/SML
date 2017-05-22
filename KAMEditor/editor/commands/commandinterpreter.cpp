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

std::vector<Command*> CommandInterpreter::getCommands()
{
    return commands;
}

unsigned int CommandInterpreter::getSelectedCommand()
{
    return selectedCommand;
}

void CommandInterpreter::setSelectedCommand(unsigned int number)
{
    selectedCommand = number;
}

bool CommandInterpreter::getSelectedCommandEditSignal()
{
    return selectedCommandEditSignal;
}

void CommandInterpreter::setSelectedCommandEditSignal(bool value)
{
    selectedCommandEditSignal = value;
}

void CommandInterpreter::addCommand(Command *cmd, unsigned int selected_command)
{
    auto commandInsertIt = commands.begin() + selected_command;
    commands.insert(commandInsertIt, 1, cmd);
}

void CommandInterpreter::editCommand(Command *cmd, unsigned int number)
{
    auto commandEditIt = commands.begin() + number;
    *commandEditIt = cmd;
}

void CommandInterpreter::deleteCommand(unsigned int number)
{
    if (number < commands.size())
        commands.erase(commands.begin() + number);
}

void CommandInterpreter::deleteCommands(unsigned int begin, unsigned int end)
{
    if(begin < commands.size() && end < commands.size())
    {
        auto beginIt = commands.begin() + begin;
        auto endIt = commands.begin() + end + 1;
        commands.erase(beginIt, endIt);
    }
    selectedCommand = 0;
}

void CommandInterpreter::Step()
{
    /*
    if (currentCommand < commands.size())
    {
        Command* cmd = commands[currentCommand];
        cmd->send();

        switch (cmd->getId()) {
        case CMD_CALL:
            callStack.push(currentCommand + 1);
            // поменять на что-то типа: currentCommand = dynamic_cast<Call*>(cmd)->callee();
            break;

        case CMD_RETURN:
            currentCommand = callStack.top();
            callStack.pop();
            break;

        case CMD_FOR:
            //loopStack.push(std::make_pair(currentCommand, std::stoi(cmd.args[0]) ));
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
            //labelsMap.insert( std::make_pair(cmd.args[0], currentCommand) );
            break;

        case CMD_GOTO:
            //currentCommand = labelsMap[ cmd.args[0] ];
            break;

        case CMD_END:
            Stop();
            break;

        default:
            currentCommand++;
            break;
        }
    }*/
}

void CommandInterpreter::Run()
{
    running = true;

    //t = std::thread(&_Run, this);
    t.detach();
}

void CommandInterpreter::_Run()
{
    /*
    while (running && ( commands[currentCommand].id != CMD_END ))
        Step();*/
}

void CommandInterpreter::Stop()
{
    running = false;
}

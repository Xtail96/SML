#include "commandsinterpreter.h"

CommandsInterpreter::CommandsInterpreter(CommandsManager *_commandsManager) :
    commandsManager(_commandsManager)
{
    makeProgram();
}

CommandsInterpreter::~CommandsInterpreter()
{
}

std::shared_ptr<Command> &CommandsInterpreter::operator[](size_t idx)
{
    if (idx < m_commands.size())
    {
        return m_commands[idx];
    }
    else
    {
        std::string errMsg = "Нет команды с номером " + std::to_string(idx);
        errMsg += " (всего " + std::to_string(m_commands.size()) + " команд)";
        throw std::out_of_range(errMsg);
    }
}

unsigned int CommandsInterpreter::commandsCount()
{
    return m_commands.size();
}

void CommandsInterpreter::updateProgram()
{
    makeProgram();
}

void CommandsInterpreter::makeProgram()
{
    m_commands.clear();
    for(unsigned int i = 0; i < commandsManager->commandsCount(); i++)
    {
        m_commands.push_back(commandsManager->operator [](i));
    }
}

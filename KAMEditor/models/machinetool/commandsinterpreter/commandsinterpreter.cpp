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
        m_commands.push_back(std::shared_ptr<Command>(commandsManager->operator [](i)));
    }

     m_commands = inlineVariables(m_commands);
}

std::vector<std::shared_ptr<Command> > CommandsInterpreter::inlineVariables(std::vector<std::shared_ptr<Command> > commands)
{
    std::vector<std::shared_ptr<Command> > tmpCommands = commands;
    for(auto command : tmpCommands)
    {
        if(command->getId() == CMD_VARIABLE)
        {
            QStringList variableArguments = command->getArguments();
            commands = inlineVariable(variableArguments[0], variableArguments[1], commands);
        }
    }
    return commands;
}

std::vector<std::shared_ptr<Command> > CommandsInterpreter::inlineVariable(QString key, QString value, std::vector<std::shared_ptr<Command> > commands)
{
    for(auto command : commands)
    {
        size_t id = command->getId();
        if(id != CMD_VARIABLE)
        {
            QStringList arguments = command->getArguments();
            if(arguments.contains(key))
            {
                for(int i = 0; i < arguments.size(); i++)
                {
                    if(arguments[i] == key)
                    {
                        arguments[i] = value;
                    }
                }
            }
            command->setArguments(arguments);
        }
    }
    return commands;
}


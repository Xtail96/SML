#include "commandsinterpreter.h"

CommandsInterpreter::CommandsInterpreter()
{
}

CommandsInterpreter::~CommandsInterpreter()
{
}

std::vector< std::shared_ptr<Command> > CommandsInterpreter::updateProgram(
        std::vector< std::shared_ptr<Command> > commands,
        PointsManager* pointsManager,
        DevicesManager* devicesManager)
{
    return makeProgram(commands, pointsManager, devicesManager);
}

std::vector< std::shared_ptr<Command> > CommandsInterpreter::makeProgram(
        std::vector< std::shared_ptr<Command> > commands,
        PointsManager* pointsManager,
        DevicesManager* devicesManager)
{
    std::vector< std::shared_ptr<Command> > m_commands;

    for(unsigned int i = 0; i < commands.size(); i++)
    {
        std::shared_ptr<Command> cmd = commands[i];
        m_commands.push_back(CommandsBuilder::buildCommand(cmd->getId(), cmd->getArguments(), pointsManager, devicesManager));
    }

    m_commands = inlineVariables(m_commands);
    return m_commands;
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


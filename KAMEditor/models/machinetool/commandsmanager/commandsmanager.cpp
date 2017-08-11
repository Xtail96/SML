#include "commandsmanager.h"

CommandsManager::CommandsManager(std::vector<std::shared_ptr<Command> > cmds) :
    m_commands(cmds)
{
}

std::shared_ptr<Command>& CommandsManager::operator[](size_t idx)
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

std::vector<std::shared_ptr<Command> >& CommandsManager::getCommands()
{
    return m_commands;
}

void CommandsManager::addCommand(Command *cmd)
{
    addCommand(std::shared_ptr<Command>(cmd));
}

void CommandsManager::addCommand(std::shared_ptr<Command> cmd)
{
    m_commands.push_back(cmd);
}

void CommandsManager::deleteCommand(Command *cmd)
{
    deleteCommand(std::shared_ptr<Command>(cmd));
}

void CommandsManager::deleteCommand(std::shared_ptr<Command> cmd)
{
    m_commands.erase( std::remove(m_commands.begin(), m_commands.end(), cmd), m_commands.end() );
}

void CommandsManager::deleteCommand(size_t idx)
{
    if (idx < m_commands.size())
    {
        m_commands.erase(m_commands.begin() + idx);
    }
    else
    {
        std::string errMsg = "Нет команды с номером " + std::to_string(idx);
        errMsg += " (всего " + std::to_string(m_commands.size()) + " команд)";

        throw std::out_of_range(errMsg);
    }
}

void CommandsManager::insertCommand(size_t pos, std::shared_ptr<Command> cmd)
{
    if (pos < m_commands.size())
    {
        m_commands.insert(m_commands.begin() + pos, cmd);
    }
    else
    {
        m_commands.push_back(cmd);
    }
}

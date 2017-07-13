#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <algorithm>
#include <memory>
#include "commands/command.h"

class CommandsManager
{
public:
    /**
     * @brief Создает менеджер команд
     * @param cmds вектор добавляемых команд (необязательный параметр)
     */
    CommandsManager(std::vector< std::shared_ptr<Command> > cmds =
            std::vector< std::shared_ptr<Command> >());

    /**
     * @brief Возвращает команду по заданному номеру
     * @param idx номер требуемой команды
     * @return ссылку на команду (на указатель на команду)
     * \warning Если idx превышает число команд, бросает исключение out_of_range
     */
    std::shared_ptr<Command>& operator[](size_t idx);

    /**
     * @return ссылку на список всех текущих команд
     */
    std::vector< std::shared_ptr<Command> >& getCommands();

    /**
     * @brief Добавляет команду в список команд
     * @param cmd указатель на добавляемую команду
     */
    void addCommand(Command* cmd);

    /**
     * @brief Добавляет команду в список команд
     * @param cmd умный указатель на добавляемую команду
     */
    void addCommand(std::shared_ptr<Command> cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param cmd указатель на удаляемую команду
     */
    void deleteCommand(Command* cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param cmd умный указатель на удаляемую команду
     */
    void deleteCommand(std::shared_ptr<Command> cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param idx номер удаляемой команды
     * \warning Если idx превышает число команд, бросает исключение out_of_range
     */
    void deleteCommand(size_t idx);

private:
    /// Список всех команд
    std::vector< std::shared_ptr<Command> > m_commands;
};

#endif // COMMANDSMANAGER_H

#ifndef COMMANDSMANAGER_H
#define COMMANDSMANAGER_H

#include <algorithm>
#include <memory>

#include "commands/smlcommand.h"

class SMLCommand;

/**
 * @brief Класс Менеджер команд
 * Взаимодействие с SML-командами происходит через этот класс
 */
class CommandsManager
{
public:
    /**
     * @brief Создает менеджер команд
     * @param cmds вектор добавляемых команд (необязательный параметр)
     */
    CommandsManager(std::vector< std::shared_ptr<SMLCommand> > cmds =
            std::vector< std::shared_ptr<SMLCommand> >());

    /**
     * @brief Конструктор копирования для класса Менеджер команд
     * @param object ссылка на объект класса Менеджер команд
     */
    CommandsManager(const CommandsManager &object);

    /**
     * @brief Возвращает команду по заданному номеру
     * @param idx номер требуемой команды
     * @return ссылку на команду (на указатель на команду)
     * \warning Если idx превышает число команд, бросает исключение out_of_range
     */
    std::shared_ptr<SMLCommand>& operator[](size_t idx);

    /**
     * @brief Возвращает число команд
     * @return число команд
     */
    unsigned int commandsCount();

    /**
     * @brief Добавляет команду в список команд
     * @param cmd указатель на добавляемую команду
     */
    void addCommand(SMLCommand* cmd);

    /**
     * @brief Добавляет команду в список команд
     * @param cmd умный указатель на добавляемую команду
     */
    void addCommand(std::shared_ptr<SMLCommand> cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param cmd указатель на удаляемую команду
     */
    void deleteCommand(SMLCommand* cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param cmd умный указатель на удаляемую команду
     */
    void deleteCommand(std::shared_ptr<SMLCommand> cmd);

    /**
     * @brief Удаляет команду из списка команд
     * @param idx номер удаляемой команды
     * \warning Если idx превышает число команд, бросает исключение out_of_range
     */
    void deleteCommand(size_t idx);

    /**
     * @brief Удаляет команды из списка команд
     * @param beginIdx номер начальной команды
     * @param endIdx номер конечной команды
     */
    void deleteCommands(size_t beginIdx, size_t endIdx);

    /**
     * @brief Вставляет команду в список команд по заданному индексу
     * @param pos индекс, по которому вставится команда
     * @param cmd команда
     *
     * Если pos превышает размер списка, вставка происходит в конец списка
     */
    void insertCommand(size_t pos, std::shared_ptr<SMLCommand> cmd);


private:
    /// Список всех выбранных команд
    std::vector< std::shared_ptr<SMLCommand> > m_commands;
};

#endif // COMMANDSMANAGER_H

#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <thread>
#include <stack>
#include <string>
#include <map>

#include "models/machinetool/commandsmanager/commandsmanager.h"

class CommandsManager;
class Command;
class PointsManager;
class DevicesManager;

class CommandsInterpreter
{
public:
    CommandsInterpreter();
    ~CommandsInterpreter();

    /**
     * @brief Возвращает команду по заданному номеру
     * @param idx номер требуемой команды
     * @return ссылку на команду (на указатель на команду)
     * \warning Если idx превышает число команд, бросает исключение out_of_range
     */
    std::shared_ptr<Command>& operator[](size_t idx);

    /**
     * @brief Возвращает число команд
     * @return число команд
     */
    unsigned int commandsCount();

    void updateProgram(CommandsManager *commandsManager, PointsManager *pointsManager, DevicesManager *devicesManager);

    void makeProgram(CommandsManager *commandsManager, PointsManager *pointsManager, DevicesManager *devicesManager);

    static std::vector< std::shared_ptr<Command> > inlineVariables(std::vector< std::shared_ptr<Command> > commands);
    static std::vector< std::shared_ptr<Command> > inlineVariable(QString key, QString value, std::vector<std::shared_ptr<Command> > commands);

private:
    std::vector< std::shared_ptr<Command> > m_commands;
};

#endif // COMMANDINTERPRETER_H

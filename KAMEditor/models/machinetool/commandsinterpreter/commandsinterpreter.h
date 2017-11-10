#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <thread>
#include <stack>
#include <string>
#include <map>

#include "models/machinetool/commandsmanager/commands/commandsbuilder.h"

class PointsManager;
class DevicesManager;

class CommandsInterpreter
{
public:
    CommandsInterpreter();
    ~CommandsInterpreter();

    static std::vector< std::shared_ptr<Command> > updateProgram(std::vector< std::shared_ptr<Command> > commands,
                              PointsManager* pointsmanager,
                              DevicesManager* devicesManager);


    static std::vector< std::shared_ptr<Command> > makeProgram(std::vector< std::shared_ptr<Command> > commands,
                            PointsManager* pointsManager,
                            DevicesManager* devicesManager);
private:
    static std::vector< std::shared_ptr<Command> > inlineVariables(std::vector< std::shared_ptr<Command> > commands);
    static std::vector< std::shared_ptr<Command> > inlineVariable(QString key, QString value, std::vector<std::shared_ptr<Command> > commands);
    static std::vector< std::shared_ptr<Command> > eraseVariables(QList<size_t> indexes, std::vector<std::shared_ptr<Command> > commands);
};

#endif // COMMANDINTERPRETER_H

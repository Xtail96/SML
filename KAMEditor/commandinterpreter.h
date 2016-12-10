#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include <thread>
#include <stack>
#include <string>
#include <map>

#include "commandhandler.h"



class CommandInterpreter
{
public:
    void Run();
    void Stop();
    void Step();

    void addCommand(Command cmd);

    static CommandInterpreter& Instance();

private:
    bool running;

    void _Run();

    std::thread t;

    unsigned int currentCommand;
    std::vector<Command> commands;


    std::stack<int> callStack;
    std::stack<std::pair<int, int> > loopStack;
    std::map<std::string, int> functionsMap;
    std::map<std::string, int> labelsMap;


    CommandInterpreter();
    ~CommandInterpreter();

    CommandInterpreter(const CommandInterpreter&);
    CommandInterpreter& operator=(const CommandInterpreter&);
};

#endif // COMMANDINTERPRETER_H

#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H


class CommandInterpreter
{
public:
    static CommandInterpreter& Instance();

private:
    // конструктор и деструктор недоступны публично
    CommandInterpreter();
    ~CommandInterpreter();

    // запрет копирования
    CommandInterpreter(CommandInterpreter const&);
    CommandInterpreter& operator=(CommandInterpreter const&);
};

#endif // COMMANDINTERPRETER_H

#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H
#include <QLineEdit>
#include "../../models/machinetool/commandsinterpreter/commandsinterpreter.h"

class CommandDialog
{
public:
    CommandDialog();
    ~CommandDialog();
protected:
    void fillFields(std::vector<QLineEdit*> &fields);
    void setCommandArguments(Command &cmd);
};

#endif // COMMANDDIALOG_H

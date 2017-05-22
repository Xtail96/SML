#ifndef COMMANDDIALOG_H
#define COMMANDDIALOG_H
#include <QLineEdit>
#include "../../editor/commands/commandinterpreter.h"

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

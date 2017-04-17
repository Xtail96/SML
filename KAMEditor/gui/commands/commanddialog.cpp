#include "commanddialog.h"

CommandDialog::CommandDialog()
{

}
CommandDialog::~CommandDialog()
{
    CommandInterpreter &instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}

void CommandDialog::fillFields(std::vector<QLineEdit *> &fields)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        for(unsigned int i = 0; i < fields.size(); i++)
        {
            fields[i]->setText(QString::fromStdString(current_command_arguments[i]));
        }
    }
}

void CommandDialog::setCommandArguments(Command &cmd)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();

    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
       instance.editCommandsArguments(cmd.args, selected_command);
       instance.setSelectedCommandEditSignal(false);
    }
    else
    {
        instance.addCommand(cmd, selected_command);
    }
}

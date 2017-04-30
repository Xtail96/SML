#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OffDialog)
{
    ui->setupUi(this);
    fillFields();
}

OffDialog::~OffDialog()
{
    delete ui;
}

void OffDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_OFF;

    cmd.commandColor = COMMANDCOLORS[safeColor];


    std::string argument;

    if(ui->spindle_off_checkBox->isChecked())
    {
        argument = "Шпиндель";
        cmd.args.push_back(argument);
        argument = "";
    }

    if(ui->kabriol_off_checkBox->isChecked())
    {
        argument = "Кабриоль";
        cmd.args.push_back(argument);
        argument ="";
    }
    setCommandArguments(cmd);
}

void OffDialog::fillFields()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;

        for(unsigned int i = 0; i < current_command_arguments.size(); i++)
        {
            if(current_command_arguments[i] == "Шпиндель")
            {
                ui->spindle_off_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "Кабриоль")
            {
                ui->kabriol_off_checkBox->setChecked(true);
            }
        }
    }
}

#include "cycledialog.h"
#include "ui_cycledialog.h"

CycleDialog::CycleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CycleDialog)
{
    ui->setupUi(this);
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->cycle_amount_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
    }
}

CycleDialog::~CycleDialog()
{
    delete ui;
}

void CycleDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_FOR;

    cmd.commandColor = "#999900";

    int amount = ui->cycle_amount_lineEdit->text().toInt();
    cmd.args = {
     std::to_string(amount),
    };

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

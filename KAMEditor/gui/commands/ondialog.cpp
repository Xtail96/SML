#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnDialog)
{
    ui->setupUi(this);
    QFile description("./description/on.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->action_on_textEdit_description->setHtml(content);
    description.close();

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
                ui->spindle_on_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "Кабриоль")
            {
                ui->kabriol_on_checkBox->setChecked(true);
            }
        }
    }
}

OnDialog::~OnDialog()
{
    delete ui;
}

void OnDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ON;

    cmd.commandColor = "#990000";


    std::string argument;

    if(ui->spindle_on_checkBox->isChecked())
    {
        argument = "Шпиндель";
        cmd.args.push_back(argument);
        argument = "";
    }

    if(ui->kabriol_on_checkBox->isChecked())
    {
        argument = "Кабриоль";
        cmd.args.push_back(argument);
        argument ="";
    }

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

void OnDialog::on_OnDialog_rejected()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}

#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OffDialog)
{
    ui->setupUi(this);
}

OffDialog::~OffDialog()
{
    delete ui;
}

void OffDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_OFF;

    cmd.commandColor = "#009900";


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

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}

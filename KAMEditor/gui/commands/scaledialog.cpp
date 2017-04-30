#include "scaledialog.h"
#include "ui_scaledialog.h"

ScaleDialog::ScaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleDialog)
{
    ui->setupUi(this);
    fillFields();
}

ScaleDialog::~ScaleDialog()
{
    delete ui;
}

void ScaleDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_SCALEX;

    cmd.commandColor = COMMANDCOLORS[modifyColor];

    std::string oldScale  = ui->old_scale_lineEdit->text().toStdString();
    cmd.args.push_back(oldScale);

    std::string newScale  = ui->new_scale_lineEdit->text().toStdString();
    cmd.args.push_back(newScale);

    std::string axis;
    if(ui->x_axis_checkBox->isChecked())
    {
        axis = "По оси X";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->y_axis_checkBox->isChecked())
    {
        axis = "По оси Y";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->z_axis_checkBox->isChecked())
    {
        axis = "По оси Z";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->a_axis_checkBox->isChecked())
    {
        axis = "По оси A";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->b_axis_checkBox->isChecked())
    {
        axis = "По оси B";
        cmd.args.push_back(axis);
        axis = "";
    }

    if(ui->relative_checkBox->isChecked())
    {
        std::string relative;
        relative = "Относительный";
        cmd.args.push_back(relative);
        relative = "";
    }
    setCommandArguments(cmd);
}

void ScaleDialog::fillFields()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->old_scale_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
        ui->new_scale_lineEdit->setText(QString::fromStdString(current_command_arguments[1]));
        for(unsigned int i = 0; i < current_command_arguments.size(); i++)
        {
            if(current_command_arguments[i] == "Относительный")
            {
                ui->relative_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "По оси X")
            {
                ui->x_axis_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "По оси Y")
            {
                ui->y_axis_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "По оси Z")
            {
                ui->z_axis_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "По оси A")
            {
                ui->a_axis_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "По оси B")
            {
                ui->b_axis_checkBox->setChecked(true);
            }
        }
    }
}

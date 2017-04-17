#include "rotatedialog.h"
#include "ui_rotatedialog.h"

RotateDialog::RotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateDialog)
{
    ui->setupUi(this);
    fillFields();
}

RotateDialog::~RotateDialog()
{
    delete ui;
}

void RotateDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ROTATE;

    cmd.commandColor = "#770077";



    int angle_value = ui->rotate_angle_lineEdit->text().toInt();
    std::string angle  = std::to_string(angle_value);
    cmd.args.push_back(angle);

    std::string axis;
    if(ui->rotate_radioButton_axis_x->isChecked())
    {
        axis = "Вокруг оси X";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_y->isChecked())
    {
        axis = "Вокруг оси Y";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_z->isChecked())
    {
        axis = "Вокруг оси Z";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_a->isChecked())
    {
        axis = "Вокруг оси A";
        cmd.args.push_back(axis);
        axis = "";
    }
    if(ui->rotate_radioButton_axis_b->isChecked())
    {
        axis = "Вокруг оси B";
        cmd.args.push_back(axis);
        axis = "";
    }

    if(ui->rotate_relative_checkBox->isChecked())
    {
        std::string relative;
        relative = "Относительный";
        cmd.args.push_back(relative);
        relative = "";
    }
    setCommandArguments(cmd);
}

void RotateDialog::fillFields()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;

        ui->rotate_angle_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));

        for(unsigned int i = 0; i < current_command_arguments.size(); i++)
        {
            if(current_command_arguments[i] == "Относительный")
            {
                ui->rotate_relative_checkBox->setChecked(true);
            }
            if(current_command_arguments[i] == "Вокруг оси X")
            {
                ui->rotate_radioButton_axis_x->setChecked(true);
            }
            if(current_command_arguments[i] == "Вокруг оси Y")
            {
                ui->rotate_radioButton_axis_y->setChecked(true);
            }
            if(current_command_arguments[i] == "Вокруг оси Z")
            {
                ui->rotate_radioButton_axis_z->setChecked(true);
            }
            if(current_command_arguments[i] == "Вокруг оси A")
            {
                ui->rotate_radioButton_axis_a->setChecked(true);
            }
            if(current_command_arguments[i] == "Вокруг оси B")
            {
                ui->rotate_radioButton_axis_b->setChecked(true);
            }
        }
    }
}

#include "ttttsplinedialog.h"
#include "ui_ttttsplinedialog.h"

TTTTSplineDialog::TTTTSplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTTSplineDialog)
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

        ui->ttttspline_start_point_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
        ui->ttttspline_middle_point_first_lineEdit->setText(QString::fromStdString(current_command_arguments[1]));
        ui->ttttspline_middle_point_second_lineEdit->setText(QString::fromStdString(current_command_arguments[2]));
        ui->ttttspline_finish_point_lineEdit->setText(QString::fromStdString(current_command_arguments[3]));
        ui->ttttspline_velocity_lineEdit->setText(QString::fromStdString(current_command_arguments[4]));
    }
}

TTTTSplineDialog::~TTTTSplineDialog()
{
    delete ui;
}

void TTTTSplineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTTTSPLINE;

    int startPoint = ui->ttttspline_start_point_lineEdit->text().toInt();
    int middlePointFirst = ui->ttttspline_middle_point_first_lineEdit->text().toInt();
    int middlePointSecond = ui->ttttspline_middle_point_second_lineEdit->text().toInt();
    int finishPoint = ui->ttttspline_finish_point_lineEdit->text().toInt();
    int velocity = ui->ttttspline_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
     std::to_string(startPoint),
     std::to_string(middlePointFirst),
     std::to_string(middlePointSecond),
     std::to_string(finishPoint),
     std::to_string(velocity),
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

#include "splinedialog.h"
#include "ui_splinedialog.h"

SplineDialog::SplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplineDialog)
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

        ui->spline_start_point_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
        ui->spline_output_angle_point_lineEdit->setText(QString::fromStdString(current_command_arguments[1]));
        ui->spline_input_angle_point_lineEdit->setText(QString::fromStdString(current_command_arguments[2]));
        ui->spline_finish_point_lineEdit->setText(QString::fromStdString(current_command_arguments[3]));
        ui->spline_velocity_lineEdit->setText(QString::fromStdString(current_command_arguments[4]));
    }
}

SplineDialog::~SplineDialog()
{
    delete ui;
}

void SplineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_SPLINE;

    int startPoint = ui->spline_start_point_lineEdit->text().toInt();
    int outputAnglePoint = ui->spline_output_angle_point_lineEdit->text().toInt();
    int inputAnglePoint = ui->spline_input_angle_point_lineEdit->text().toInt();
    int finishPoint = ui->spline_finish_point_lineEdit->text().toInt();
    int velocity = ui->spline_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
     std::to_string(startPoint),
     std::to_string(outputAnglePoint),
     std::to_string(inputAnglePoint),
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

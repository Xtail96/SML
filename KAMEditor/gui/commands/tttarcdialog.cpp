#include "tttarcdialog.h"
#include "ui_tttarcdialog.h"

TTTArcDialog::TTTArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTArcDialog)
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

        ui->ttt_arc_start_point_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
        ui->ttt_arc_middle_point_lineEdit->setText(QString::fromStdString(current_command_arguments[1]));
        ui->ttt_arc_finish_point_lineEdit->setText(QString::fromStdString(current_command_arguments[2]));
        ui->ttt_arc_velocity_lineEdit->setText(QString::fromStdString(current_command_arguments[3]));
    }
}

TTTArcDialog::~TTTArcDialog()
{
    delete ui;
}

void TTTArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTTARC;

    int startPoint = ui->ttt_arc_start_point_lineEdit->text().toInt();
    int middlePoint = ui->ttt_arc_middle_point_lineEdit->text().toInt();
    int finishPoint = ui->ttt_arc_finish_point_lineEdit->text().toInt();
    int velocity = ui->ttt_arc_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
        std::to_string(startPoint),
        std::to_string(middlePoint),
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

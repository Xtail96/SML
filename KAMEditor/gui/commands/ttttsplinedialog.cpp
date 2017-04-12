#include "ttttsplinedialog.h"
#include "ui_ttttsplinedialog.h"

TTTTSplineDialog::TTTTSplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTTSplineDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttttspline_start_point_lineEdit,
        ui->ttttspline_middle_point_first_lineEdit,
        ui->ttttspline_middle_point_second_lineEdit,
        ui->ttttspline_finish_point_lineEdit,
        ui->ttttspline_velocity_lineEdit
    };
    fillFields(fields);
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

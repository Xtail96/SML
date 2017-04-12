#include "splinedialog.h"
#include "ui_splinedialog.h"

SplineDialog::SplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplineDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->spline_start_point_lineEdit,
        ui->spline_output_angle_point_lineEdit,
        ui->spline_input_angle_point_lineEdit,
        ui->spline_finish_point_lineEdit,
        ui->spline_velocity_lineEdit
    };
    fillFields(fields);
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
    setCommandArguments(cmd);
}

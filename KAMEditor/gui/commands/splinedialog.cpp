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

    std::string startPoint = ui->spline_start_point_lineEdit->text().toStdString();
    std::string outputAnglePoint = ui->spline_output_angle_point_lineEdit->text().toStdString();
    std::string inputAnglePoint = ui->spline_input_angle_point_lineEdit->text().toStdString();
    std::string finishPoint = ui->spline_finish_point_lineEdit->text().toStdString();
    std::string velocity = ui->spline_velocity_lineEdit->text().toStdString();

    cmd.commandColor = COMMANDCOLORS[defaultColor];

    cmd.args = {
     startPoint,
     outputAnglePoint,
     inputAnglePoint,
     finishPoint,
     velocity,
    };
    setCommandArguments(cmd);
}

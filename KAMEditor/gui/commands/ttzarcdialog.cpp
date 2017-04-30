#include "ttzarcdialog.h"
#include "ui_ttzarcdialog.h"

TTZArcDialog::TTZArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTZArcDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttz_arc_start_point_lineEdit,
        ui->ttz_arc_finish_point_lineEdit,
        ui->ttz_arc_radius_lineEdit,
        ui->ttz_arc_dz_lineEdit,
        ui->ttz_arc_a_axis_lineEdit,
        ui->ttz_arc_velocity_lineEdit
    };
    fillFields(fields);
}

TTZArcDialog::~TTZArcDialog()
{
    delete ui;
}

void TTZArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTZARC;

    std::string startPoint = ui->ttz_arc_start_point_lineEdit->text().toStdString();
    std::string finishPoint = ui->ttz_arc_finish_point_lineEdit->text().toStdString();
    std::string radius = ui->ttz_arc_radius_lineEdit->text().toStdString();
    std::string dz = ui->ttz_arc_dz_lineEdit->text().toStdString();
    std::string angle = ui->ttz_arc_a_axis_lineEdit->text().toStdString();
    std::string velocity = ui->ttz_arc_velocity_lineEdit->text().toStdString();

    cmd.commandColor = COMMANDCOLORS[defaultColor];

    cmd.args = {
        startPoint,
        finishPoint,
        radius,
        dz,
        angle,
        velocity,
    };
    setCommandArguments(cmd);
}

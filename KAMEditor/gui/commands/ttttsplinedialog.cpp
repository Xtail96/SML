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

    std::string startPoint = ui->ttttspline_start_point_lineEdit->text().toStdString();
    std::string middlePointFirst = ui->ttttspline_middle_point_first_lineEdit->text().toStdString();
    std::string middlePointSecond = ui->ttttspline_middle_point_second_lineEdit->text().toStdString();
    std::string finishPoint = ui->ttttspline_finish_point_lineEdit->text().toStdString();
    std::string velocity = ui->ttttspline_velocity_lineEdit->text().toStdString();

    cmd.commandColor = "#333";

    cmd.args = {
     startPoint,
     middlePointFirst,
     middlePointSecond,
     finishPoint,
     velocity
    };
    setCommandArguments(cmd);
}

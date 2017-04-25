#include "ttlinedialog.h"
#include "ui_ttlinedialog.h"

TTLineDialog::TTLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTLineDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttline_start_point_lineEdit,
        ui->ttline_finish_point_lineEdit,
        ui->ttline_dz_lineEdit,
        ui->ttline_velocity_lineEdit,
        ui->ttline_a_coordinate_lineEdit
    };
    fillFields(fields);
}

TTLineDialog::~TTLineDialog()
{
    delete ui;
}

void TTLineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTLINE;
    std::string startPoint = ui->ttline_start_point_lineEdit->text().toStdString();
    std::string finishPoint = ui->ttline_finish_point_lineEdit->text().toStdString();
    std::string velocity = ui->ttline_velocity_lineEdit->text().toStdString();
    std::string dzOffset = ui->ttline_dz_lineEdit->text().toStdString();
    std::string aCoordinate = ui->ttline_a_coordinate_lineEdit->text().toStdString();
    cmd.commandColor = "#333";
    cmd.args = {
     startPoint,
     finishPoint,
     dzOffset,
     velocity,
     aCoordinate
    };
    setCommandArguments(cmd);
}

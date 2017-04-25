#include "tttarcdialog.h"
#include "ui_tttarcdialog.h"

TTTArcDialog::TTTArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTArcDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttt_arc_start_point_lineEdit,
        ui->ttt_arc_middle_point_lineEdit,
        ui->ttt_arc_finish_point_lineEdit,
        ui->ttt_arc_velocity_lineEdit
    };
    fillFields(fields);
}

TTTArcDialog::~TTTArcDialog()
{
    delete ui;
}

void TTTArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTTARC;

    std::string startPoint = ui->ttt_arc_start_point_lineEdit->text().toStdString();
    std::string middlePoint = ui->ttt_arc_middle_point_lineEdit->text().toStdString();
    std::string finishPoint = ui->ttt_arc_finish_point_lineEdit->text().toStdString();
    std::string velocity = ui->ttt_arc_velocity_lineEdit->text().toStdString();

    cmd.commandColor = "#333";
    cmd.args = {
        startPoint,
        middlePoint,
        finishPoint,
        velocity
    };
    setCommandArguments(cmd);
}

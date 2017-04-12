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
    setCommandArguments(cmd);
}

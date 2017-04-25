#include "arc2dialog.h"
#include "ui_arc2dialog.h"

Arc2Dialog::Arc2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arc2Dialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->arc2_dx_lineEdit,
         ui->arc2_dy_lineEdit,
         ui->arc2_r_lineEdit,
         ui->arc2_velocity_lineEdit,
         ui->arc2_a_lineEdit
    };
    fillFields(fields);
}

Arc2Dialog::~Arc2Dialog()
{
    delete ui;
}

void Arc2Dialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ARC2;

    cmd.commandColor = "#333";

    double dx = ui->arc2_dx_lineEdit->text().toDouble();
    double dy = ui->arc2_dy_lineEdit->text().toDouble();
    double r = ui->arc2_r_lineEdit->text().toDouble();
    int velocity = ui->arc2_velocity_lineEdit->text().toInt();
    double a = ui->arc2_a_lineEdit->text().toDouble();

    cmd.args = {
     std::to_string(dx),
     std::to_string(dy),
     std::to_string(r),
     std::to_string(velocity),
     std::to_string(a)
    };
    setCommandArguments(cmd);
}

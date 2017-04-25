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

    std::string dx = ui->arc2_dx_lineEdit->text().toStdString();
    std::string dy = ui->arc2_dy_lineEdit->text().toStdString();
    std::string r = ui->arc2_r_lineEdit->text().toStdString();
    std::string velocity = ui->arc2_velocity_lineEdit->text().toStdString();
    std::string a = ui->arc2_a_lineEdit->text().toStdString();

    cmd.args = {
     dx,
     dy,
     r,
     velocity,
     a
    };
    setCommandArguments(cmd);
}

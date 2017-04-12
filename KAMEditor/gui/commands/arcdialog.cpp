#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->arc_lineEdit_r,
         ui->arc_lineEdit_al,
         ui->arc_lineEdit_fi,
         ui->arc_lineEdit_velocity
    };
    fillFields(fields);
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ARC;

    cmd.commandColor = "#333";

    double r = ui->arc_lineEdit_r->text().toDouble();
    double al = ui->arc_lineEdit_al->text().toDouble();
    double fi = ui->arc_lineEdit_fi->text().toDouble();
    int velocity = ui->arc_lineEdit_velocity->text().toInt();

    cmd.args = {
     std::to_string(r),
     std::to_string(al),
     std::to_string(fi),
     std::to_string(velocity),
    };
    setCommandArguments(cmd);
}

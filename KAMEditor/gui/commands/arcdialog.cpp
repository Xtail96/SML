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

    std::string r = ui->arc_lineEdit_r->text().toStdString();
    std::string al = ui->arc_lineEdit_al->text().toStdString();
    std::string fi = ui->arc_lineEdit_fi->text().toStdString();
    std::string velocity = ui->arc_lineEdit_velocity->text().toStdString();

    cmd.args = {
     r,
     al,
     fi,
     velocity,
    };
    setCommandArguments(cmd);
}

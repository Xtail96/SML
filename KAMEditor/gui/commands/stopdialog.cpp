#include "stopdialog.h"
#include "ui_stopdialog.h"

StopDialog::StopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StopDialog)
{
    ui->setupUi(this);
}

StopDialog::~StopDialog()
{
    delete ui;
}

void StopDialog::on_buttonBox_accepted()
{

}

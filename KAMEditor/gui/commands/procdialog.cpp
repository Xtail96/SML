#include "procdialog.h"
#include "ui_procdialog.h"

ProcDialog::ProcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcDialog)
{
    ui->setupUi(this);
}

ProcDialog::~ProcDialog()
{
    delete ui;
}

void ProcDialog::on_buttonBox_accepted()
{

}

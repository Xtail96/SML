#include "callprocdialog.h"
#include "ui_callprocdialog.h"

CallProcDialog::CallProcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallProcDialog)
{
    ui->setupUi(this);
}

CallProcDialog::~CallProcDialog()
{
    delete ui;
}

void CallProcDialog::on_buttonBox_accepted()
{

}

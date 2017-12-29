#include "ttzarcdialog.h"
#include "ui_ttzarcdialog.h"

TTZArcDialog::TTZArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTZArcDialog)
{
    ui->setupUi(this);
}

TTZArcDialog::~TTZArcDialog()
{
    delete ui;
}

void TTZArcDialog::on_buttonBox_accepted()
{

}

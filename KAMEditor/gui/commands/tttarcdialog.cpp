#include "tttarcdialog.h"
#include "ui_tttarcdialog.h"

TTTArcDialog::TTTArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTArcDialog)
{
    ui->setupUi(this);
}

TTTArcDialog::~TTTArcDialog()
{
    delete ui;
}

void TTTArcDialog::on_buttonBox_accepted()
{

}

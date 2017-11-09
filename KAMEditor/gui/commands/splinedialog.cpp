#include "splinedialog.h"
#include "ui_splinedialog.h"

SplineDialog::SplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplineDialog)
{
    ui->setupUi(this);
}

SplineDialog::~SplineDialog()
{
    delete ui;
}

void SplineDialog::on_buttonBox_accepted()
{

}

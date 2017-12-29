#include "velocitydialog.h"
#include "ui_velocitydialog.h"


VelocityDialog::VelocityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VelocityDialog)
{
    ui->setupUi(this);
}

VelocityDialog::~VelocityDialog()
{
    delete ui;
}

void VelocityDialog::on_buttonBox_accepted()
{

}

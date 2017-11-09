#include "rotatedialog.h"
#include "ui_rotatedialog.h"

RotateDialog::RotateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RotateDialog)
{
    ui->setupUi(this);
}

RotateDialog::~RotateDialog()
{
    delete ui;
}

void RotateDialog::on_buttonBox_accepted()
{

}

void RotateDialog::fillFields()
{

}

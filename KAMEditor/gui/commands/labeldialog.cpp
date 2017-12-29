#include "labeldialog.h"
#include "ui_labeldialog.h"

LabelDialog::LabelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LabelDialog)
{
    ui->setupUi(this);
}

LabelDialog::~LabelDialog()
{
    delete ui;
}

void LabelDialog::on_buttonBox_accepted()
{

}

#include "gotodialog.h"
#include "ui_gotodialog.h"

GoToDialog::GoToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToDialog)
{
    ui->setupUi(this);
}

GoToDialog::~GoToDialog()
{
    delete ui;
}

void GoToDialog::on_buttonBox_accepted()
{

}

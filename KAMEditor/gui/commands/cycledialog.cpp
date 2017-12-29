#include "cycledialog.h"
#include "ui_cycledialog.h"

CycleDialog::CycleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CycleDialog)
{
    ui->setupUi(this);
}

CycleDialog::~CycleDialog()
{
    delete ui;
}

void CycleDialog::on_buttonBox_accepted()
{

}

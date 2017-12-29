#include "ttttsplinedialog.h"
#include "ui_ttttsplinedialog.h"

TTTTSplineDialog::TTTTSplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTTSplineDialog)
{
    ui->setupUi(this);
}

TTTTSplineDialog::~TTTTSplineDialog()
{
    delete ui;
}

void TTTTSplineDialog::on_buttonBox_accepted()
{

}

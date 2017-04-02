#include "tttlinedialog.h"
#include "ui_tttlinedialog.h"

TTTLineDialog::TTTLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTLineDialog)
{
    ui->setupUi(this);
}

TTTLineDialog::~TTTLineDialog()
{
    delete ui;
}

void TTTLineDialog::on_buttonBox_accepted()
{

}

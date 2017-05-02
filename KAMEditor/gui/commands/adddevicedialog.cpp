#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"

AddDeviceDialog::AddDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDeviceDialog)
{
    ui->setupUi(this);
}

AddDeviceDialog::~AddDeviceDialog()
{
    delete ui;
}

void AddDeviceDialog::on_buttonBox_accepted()
{

}

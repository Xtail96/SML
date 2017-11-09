#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::OffDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

OffDialog::~OffDialog()
{
    delete ui;
}

void OffDialog::on_buttonBox_accepted()
{
    QStringList cmdArguments =
    {
        ui->devicesComboBox->currentText()
    };
    if(!edit)
    {
        controller->insertCommand(CMD_SWITCH_OFF, cmdArguments, index);
    }
    else
    {
        controller->updateCommand(cmdArguments, index);
    }
}

void OffDialog::fillFields()
{
    QStringList devicesNames = controller->getDevicesNames();
    ui->devicesComboBox->addItems(devicesNames);

    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString deviceName = arguments[0];
        ui->devicesComboBox->setCurrentText(deviceName);
    }
}

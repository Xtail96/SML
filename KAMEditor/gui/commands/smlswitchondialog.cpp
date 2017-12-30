#include "smlswitchondialog.h"
#include "ui_smlswitchondialog.h"

SMLSwitchOnDialog::SMLSwitchOnDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLSwitchOnDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

SMLSwitchOnDialog::~SMLSwitchOnDialog()
{
    delete ui;
}

void SMLSwitchOnDialog::fillFields()
{
    QStringList devicesNames = controller->getDevicesNames();
    ui->devicesComboBox->addItems(devicesNames);
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString deviceName = arguments[0];
        ui->devicesComboBox->setCurrentText(deviceName);


        QString parametrs = "";
        for(int i = 1; i < arguments.size(); i++)
        {
            parametrs += arguments[i];
        }
        ui->argumentsLineEdit->setText(parametrs);
    }
}


void SMLSwitchOnDialog::on_buttonBox_accepted()
{
    QString parametrs = QString::number(ui->argumentsLineEdit->text().toUInt());

    QStringList cmdArguments =
    {
        ui->devicesComboBox->currentText(),
        parametrs
    };
    if(!edit)
    {
        controller->insertCommand(CMD_SWITCH_ON, cmdArguments, index);
    }
    else
    {
        controller->updateCommand(cmdArguments, index);
    }
}

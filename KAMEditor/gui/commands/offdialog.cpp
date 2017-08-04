#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OffDialog),
    machineTool(_machineTool)
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
    std::string deviceName = ui->devicesComboBox->currentText().toStdString();
    std::string parametrs = ui->argumentsLineEdit->text().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOff(machineTool, deviceName, parametrs));
    machineTool->getCommandsManager()->addCommand(cmd);
}

void OffDialog::fillFields()
{
    std::vector< std::shared_ptr<Device> > devices = machineTool->getDevicesManager()->getDevices();
    QStringList devicesNames;
    for(auto it : devices)
    {
        QString deviceName = QString::fromStdString(it->getName());
        devicesNames.push_back(deviceName);
    }
    ui->devicesComboBox->addItems(devicesNames);
}

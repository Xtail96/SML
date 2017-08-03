#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnDialog),
    machineTool(_machineTool)
{
    ui->setupUi(this);
    fillFields();
}

OnDialog::~OnDialog()
{
    delete ui;
    //delete machineTool;
}

void OnDialog::fillFields()
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

void OnDialog::on_buttonBox_accepted()
{
    std::string deviceName = ui->devicesComboBox->currentText().toStdString();
    std::string parametrs = ui->argumentsLineEdit->text().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOn(machineTool, deviceName, parametrs));
    machineTool->getCommandsManager()->addCommand(cmd);
}

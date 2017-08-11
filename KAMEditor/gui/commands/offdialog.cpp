#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(DevicesManager *_devicesManager, CommandsManager *_commandsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OffDialog),
    devicesManager(_devicesManager),
    commandsManager(_commandsManager)
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
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOff(devicesManager, deviceName, parametrs));
    commandsManager->addCommand(cmd);
}

void OffDialog::fillFields()
{
    std::vector< std::shared_ptr<Device> > devices = devicesManager->getDevices();
    QStringList devicesNames;
    for(auto it : devices)
    {
        QString deviceName = QString::fromStdString(it->getName());
        devicesNames.push_back(deviceName);
    }
    ui->devicesComboBox->addItems(devicesNames);
}

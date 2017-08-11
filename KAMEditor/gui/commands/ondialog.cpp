#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(DevicesManager *_devicesManager, CommandsManager *_commandsManager, int _position, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnDialog),
    devicesManager(_devicesManager),
    commandsManager(_commandsManager),
    position(_position)
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
    std::vector< std::shared_ptr<Device> > devices = devicesManager->getDevices();
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
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOn(devicesManager, deviceName, parametrs));
    commandsManager->insertCommand(position, cmd);
}

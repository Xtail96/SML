#include "offdialog.h"
#include "ui_offdialog.h"

OffDialog::OffDialog(DevicesManager *_devicesManager, CommandsManager *_commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::OffDialog),
    devicesManager(_devicesManager),
    commandsManager(_commandsManager),
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
    std::string deviceName = ui->devicesComboBox->currentText().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOff(devicesManager, deviceName));
    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
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

    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();
        QString deviceName = arguments[0];
        ui->devicesComboBox->setCurrentText(deviceName);
    }
}

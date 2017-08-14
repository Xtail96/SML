#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(DevicesManager *_devicesManager, CommandsManager *_commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::OnDialog),
    devicesManager(_devicesManager),
    commandsManager(_commandsManager),
    index(_index),
    edit(_edit)
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

    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();
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

void OnDialog::on_buttonBox_accepted()
{
    std::string deviceName = ui->devicesComboBox->currentText().toStdString();
    std::string parametrs = ui->argumentsLineEdit->text().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new SwitchOn(devicesManager, deviceName, parametrs));
    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
}

#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::OnDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

OnDialog::~OnDialog()
{
    delete ui;
}

void OnDialog::fillFields()
{
    QStringList devicesNames = controller->getDevicesNames();
    ui->devicesComboBox->addItems(devicesNames);
    /*if(edit)
    {
        std::shared_ptr<Command> currentCommand = controller->getCommand(index);
        QStringList arguments = currentCommand->getArguments();
        QString deviceName = arguments[0];
        ui->devicesComboBox->setCurrentText(deviceName);


        QString parametrs = "";
        for(int i = 1; i < arguments.size(); i++)
        {
            parametrs += arguments[i];
        }
        ui->argumentsLineEdit->setText(parametrs);
    }*/
}

void OnDialog::on_buttonBox_accepted()
{    
    QStringList cmdArguments =
    {
        ui->devicesComboBox->currentText(),
        ui->argumentsLineEdit->text()
    };
    controller->insertCommand(CMD_SWITCH_ON, cmdArguments, index);
}

#include "stopdialog.h"
#include "ui_stopdialog.h"

StopDialog::StopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StopDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->stop_message_lineEdit
    };
    fillFields(fields);
}

StopDialog::~StopDialog()
{
    delete ui;
}

void StopDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_STOP;
    cmd.commandColor = "#990000";
    std::string stopMessage  = ui->stop_message_lineEdit->text().toStdString();
    cmd.args.push_back(stopMessage);
    setCommandArguments(cmd);
}

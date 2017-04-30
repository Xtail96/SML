#include "velocitydialog.h"
#include "ui_velocitydialog.h"


VelocityDialog::VelocityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VelocityDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->velocity_value_lineEdit
    };
    fillFields(fields);
}

VelocityDialog::~VelocityDialog()
{
    delete ui;
}

void VelocityDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_SPEED;

    cmd.commandColor = COMMANDCOLORS[warningColor];

    std::string velocity  = ui->velocity_value_lineEdit->text().toStdString();
    cmd.args.push_back(velocity);
    setCommandArguments(cmd);
}

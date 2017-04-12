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

    cmd.commandColor = "#770077";


    int velocityValue = ui->velocity_value_lineEdit->text().toInt();
    std::string velocity  = std::to_string(velocityValue);
    cmd.args.push_back(velocity);

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();

    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
       instance.editCommandsArguments(cmd.args, selected_command);
       instance.setSelectedCommandEditSignal(false);
    }
    else
    {
        instance.addCommand(cmd, selected_command);
    }
}

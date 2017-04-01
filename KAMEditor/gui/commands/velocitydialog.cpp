#include "velocitydialog.h"
#include "ui_velocitydialog.h"

VelocityDialog::VelocityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VelocityDialog)
{
    ui->setupUi(this);

    QFile description("./description/speed.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->velocity_description_textEdit->setHtml(content);
    description.close();

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->velocity_value_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
    }
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

#include "stopdialog.h"
#include "ui_stopdialog.h"

StopDialog::StopDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StopDialog)
{
    ui->setupUi(this);
    QFile description("./description/speed.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->stop_description_textEdit->setHtml(content);
    description.close();
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;
        ui->stop_message_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
    }
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

#include "callprocdialog.h"
#include "ui_callprocdialog.h"

CallProcDialog::CallProcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CallProcDialog)
{
    ui->setupUi(this);

    QFile description("./description/call.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->call_description_textEdit->setHtml(content);
    description.close();

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->call_name_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
    }
}

CallProcDialog::~CallProcDialog()
{
    delete ui;
}

void CallProcDialog::on_buttonBox_accepted()
{

    Command cmd;
    cmd.id = CMD_CALL;

    //cmd.commandColor = "#2f4f4f";
    cmd.commandColor = "#4682B4";


    std::string name = ui->call_name_lineEdit->text().toStdString();

    cmd.args = {
     name,
    };

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

void CallProcDialog::on_CallProcDialog_rejected()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}

#include "gotodialog.h"
#include "ui_gotodialog.h"

GoToDialog::GoToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToDialog)
{
    ui->setupUi(this);
    QFile description("./description/goto.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->goto_textEdit_description->setHtml(content);
    description.close();

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->goto_lineEdit_name->setText(QString::fromStdString(current_command_arguments[0]));
    }
}

GoToDialog::~GoToDialog()
{
    delete ui;
}

void GoToDialog::on_buttonBox_accepted()
{

    Command cmd;
    cmd.id = CMD_GOTO;

    cmd.commandColor = "#3300ff";

    std::string name = ui->goto_lineEdit_name->text().toStdString();

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

void GoToDialog::on_GoToDialog_rejected()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}

#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArcDialog)
{
    ui->setupUi(this);
    QFile description("./description/arc.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->arc_textEdit_description->setHtml(content);
    description.close();

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->arc_lineEdit_r->setText(QString::fromStdString(current_command_arguments[0]));
        ui->arc_lineEdit_al->setText(QString::fromStdString(current_command_arguments[1]));
        ui->arc_lineEdit_fi->setText(QString::fromStdString(current_command_arguments[2]));
        ui->arc_lineEdit_velocity->setText(QString::fromStdString(current_command_arguments[3]));
    }

}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ARC;

    cmd.commandColor = "#333";

    double r = ui->arc_lineEdit_r->text().toDouble();
    double al = ui->arc_lineEdit_al->text().toDouble();
    double fi = ui->arc_lineEdit_fi->text().toDouble();
    int velocity = ui->arc_lineEdit_velocity->text().toInt();

    cmd.args = {
     std::to_string(r),
     std::to_string(al),
     std::to_string(fi),
     std::to_string(velocity),
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

void ArcDialog::on_ArcDialog_rejected()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    if(instance.getSelectedCommandEditSignal())
    {
        instance.setSelectedCommandEditSignal(false);
    }
}

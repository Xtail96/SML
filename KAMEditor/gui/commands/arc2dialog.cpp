#include "arc2dialog.h"
#include "ui_arc2dialog.h"

Arc2Dialog::Arc2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arc2Dialog)
{
    ui->setupUi(this);
    QFile description("./description/arc2.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->arc2_textEdit_description->setHtml(content);
    description.close();


    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->arc2_dx_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
        ui->arc2_dy_lineEdit->setText(QString::fromStdString(current_command_arguments[1]));
        ui->arc2_r_lineEdit->setText(QString::fromStdString(current_command_arguments[2]));
        ui->arc2_a_lineEdit->setText(QString::fromStdString(current_command_arguments[3]));
        ui->arc2_velocity_lineEdit->setText(QString::fromStdString(current_command_arguments[4]));
    }

}

Arc2Dialog::~Arc2Dialog()
{
    delete ui;
}

void Arc2Dialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ARC2;

    cmd.commandColor = "#333";

    double dx = ui->arc2_dx_lineEdit->text().toDouble();
    double dy = ui->arc2_dy_lineEdit->text().toDouble();
    double r = ui->arc2_r_lineEdit->text().toDouble();
    double a = ui->arc2_a_lineEdit->text().toDouble();
    int velocity = ui->arc2_velocity_lineEdit->text().toInt();

    cmd.args = {
     std::to_string(dx),
     std::to_string(dy),
     std::to_string(r),
     std::to_string(a),
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

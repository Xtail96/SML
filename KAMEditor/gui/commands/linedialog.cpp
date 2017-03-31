#include "linedialog.h"
#include "ui_linedialog.h"

LineDialog::LineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineDialog)
{
    ui->setupUi(this);
    QFile description("./description/line.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->line_textEdit_description->setHtml(content);
    description.close();

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;


        ui->line_lineEdit_axis_x->setText(QString::fromStdString(current_command_arguments[0]));
        ui->line_lineEdit_axis_y->setText(QString::fromStdString(current_command_arguments[1]));
        ui->line_lineEdit_axis_z->setText(QString::fromStdString(current_command_arguments[2]));
        ui->line_lineEdit_axis_a->setText(QString::fromStdString(current_command_arguments[3]));
        ui->line_lineEdit_axis_b->setText(QString::fromStdString(current_command_arguments[4]));

        ui->line_lineEdit_velocity->setText(QString::fromStdString(current_command_arguments[5]));
    }

}
LineDialog::~LineDialog()
{
    delete ui;
}
void LineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_LINE;

    cmd.commandColor = "#333";

    Vector v(
    ui->line_lineEdit_axis_x->text().toDouble(),
    ui->line_lineEdit_axis_y->text().toDouble(),
    ui->line_lineEdit_axis_z->text().toDouble(),
    ui->line_lineEdit_axis_a->text().toDouble(),
    ui->line_lineEdit_axis_b->text().toDouble()
    );
    int velocity = ui->line_lineEdit_velocity->text().toInt();

    cmd.args = {
     std::to_string(v.x),
     std::to_string(v.y),
     std::to_string(v.z),
     std::to_string(v.a),
     std::to_string(v.b),
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

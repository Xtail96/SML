#include "ttlinedialog.h"
#include "ui_ttlinedialog.h"

TTLineDialog::TTLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTLineDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
        ui->ttline_start_point_lineEdit,
        ui->ttline_finish_point_lineEdit,
        ui->ttline_velocity_lineEdit
    };
    fillFields(fields);
}

TTLineDialog::~TTLineDialog()
{
    delete ui;
}

void TTLineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTLINE;

    int startPoint = ui->ttline_start_point_lineEdit->text().toInt();
    int finishPoint = ui->ttline_finish_point_lineEdit->text().toInt();
    int velocity = ui->ttline_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
     std::to_string(startPoint),
     std::to_string(finishPoint),
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

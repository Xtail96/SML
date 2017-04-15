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
        ui->ttline_velocity_lineEdit,
        ui->ttline_a_coordinate_lineEdit
    };

    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;

        for(unsigned int i = 0; i < current_command_arguments.size(); i++)
        {
            if(current_command_arguments[i] == "^")
            {
                ui->ttline_air_passage_checkBox->setChecked(true);
                if(i+1 < current_command_arguments.size())
                {
                    ui->ttline_dz_lineEdit->setText(QString::fromStdString(current_command_arguments[i+1]));
                }
            }
        }
    }

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
    std::string airPassage = "^";
    std::string dzOffset = ui->ttline_dz_lineEdit->text().toStdString();
    int aCoordinate = ui->ttline_a_coordinate_lineEdit->text().toDouble();
    cmd.commandColor = "#333";
    cmd.args = {
     std::to_string(startPoint),
     std::to_string(finishPoint),
     std::to_string(velocity),
     std::to_string(aCoordinate)
    };
    if(ui->ttline_air_passage_checkBox->isChecked())
    {
        cmd.args.push_back(airPassage);
        cmd.args.push_back(dzOffset);
    }
    setCommandArguments(cmd);
}

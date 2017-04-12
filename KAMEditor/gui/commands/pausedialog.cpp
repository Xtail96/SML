#include "pausedialog.h"
#include "ui_pausedialog.h"

PauseDialog::PauseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PauseDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->pause_value_lineEdit
    };
    fillFields(fields);
}

PauseDialog::~PauseDialog()
{
    delete ui;
}

void PauseDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_PAUSE;
    cmd.commandColor = "#990000";
    int pauseValue = ui->pause_value_lineEdit->text().toInt();
    std::string pauseArgument  = std::to_string(pauseValue);
    cmd.args.push_back(pauseArgument);

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

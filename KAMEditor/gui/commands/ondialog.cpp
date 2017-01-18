#include "ondialog.h"
#include "ui_ondialog.h"

OnDialog::OnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnDialog)
{
    ui->setupUi(this);
    QFile description("./description/on.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->action_on_textEdit_description->setHtml(content);
    description.close();
}

OnDialog::~OnDialog()
{
    delete ui;
}

void OnDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_ON;

    cmd.commandColor = "#990000";


    std::string argument;

    if(ui->spindle_on_checkBox->isChecked())
    {
        argument = "Шпиндель";
        cmd.args.push_back(argument);
        argument = "";
    }

    if(ui->kabriol_on_checkBox->isChecked())
    {
        argument = "Кабриоль";
        cmd.args.push_back(argument);
        argument ="";
    }

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}

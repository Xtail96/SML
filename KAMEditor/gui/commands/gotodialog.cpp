#include "gotodialog.h"
#include "ui_gotodialog.h"

GoToDialog::GoToDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoToDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->goto_lineEdit_name
    };
    fillFields(fields);
}

GoToDialog::~GoToDialog()
{
    delete ui;
}

void GoToDialog::on_buttonBox_accepted()
{

    Command cmd;
    cmd.id = CMD_GOTO;

    cmd.commandColor = COMMANDCOLORS[labelColor];

    std::string name = ui->goto_lineEdit_name->text().toStdString();

    cmd.args = {
     name,
    };
    setCommandArguments(cmd);
}

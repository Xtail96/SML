#include "procdialog.h"
#include "ui_procdialog.h"

ProcDialog::ProcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->proc_name_lineEdit
    };
    fillFields(fields);
}

ProcDialog::~ProcDialog()
{
    delete ui;
}

void ProcDialog::on_buttonBox_accepted()
{

    Command cmd;
    cmd.id = CMD_PROC;

    //cmd.commandColor = "#2f4f4f";
    cmd.commandColor = "#4682B4";

    std::string name = ui->proc_name_lineEdit->text().toStdString();

    cmd.args = {
     name,
    };
    setCommandArguments(cmd);
}

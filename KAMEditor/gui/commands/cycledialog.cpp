#include "cycledialog.h"
#include "ui_cycledialog.h"

CycleDialog::CycleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CycleDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->cycle_amount_lineEdit
    };
    fillFields(fields);
}

CycleDialog::~CycleDialog()
{
    delete ui;
}

void CycleDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_FOR;

    cmd.commandColor = "#999900";

    std::string amount = ui->cycle_amount_lineEdit->text().toStdString();
    cmd.args = {
     amount
    };
    setCommandArguments(cmd);
}

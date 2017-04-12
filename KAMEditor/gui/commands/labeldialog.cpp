#include "labeldialog.h"
#include "ui_labeldialog.h"

LabelDialog::LabelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LabelDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->label_lineEdit_name
    };
    fillFields(fields);
}

LabelDialog::~LabelDialog()
{
    delete ui;
}

void LabelDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_LABEL;

    cmd.commandColor = "#3300ff";

    std::string name = ui->label_lineEdit_name->text().toStdString();

    cmd.args = {
     name,
    };
    setCommandArguments(cmd);
}

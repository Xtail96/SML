#include "smlvariabledialog.h"
#include "ui_smlvariabledialog.h"

SMLVariableDialog::SMLVariableDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLVariableDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);

    fillFields();
}

SMLVariableDialog::~SMLVariableDialog()
{
    delete ui;
}

void SMLVariableDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);

        QString key = "";
        QString value = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                key = arguments[i];
                break;
            case 1:
                value = arguments[i];
                break;
            default:
                break;
            }
        }
        ui->smlVariableKeyLineEdit->setText(key);
        ui->smlVariableValueLineEdit->setText(value);
    }
}

void SMLVariableDialog::on_buttonBox_accepted()
{
    QString key = ui->smlVariableKeyLineEdit->text();
    QString value = QString::number(ui->smlVariableValueLineEdit->text().toLongLong());

    if(key.length() == 0)
    {
        key = "key";
    }

    QStringList arguments =
    {
        key,
        value
    };

    if(!edit)
    {
        controller->insertCommand(CMD_VARIABLE, arguments, index);
    }
    else
    {
        controller->updateCommand(arguments, index);
    }
}

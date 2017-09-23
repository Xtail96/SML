#include "linedialog.h"
#include "ui_linedialog.h"

LineDialog::LineDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::LineDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}
LineDialog::~LineDialog()
{
    delete ui;
}
void LineDialog::on_buttonBox_accepted()
{
    QStringList arguments =
    {
        ui->dxLineEdit->text(),
        ui->dyLineEdit->text(),
        ui->dzLineEdit->text(),
        ui->velocityLineEdit->text()
    };

    if(!edit)
    {
        controller->insertCommand(CMD_LINE, arguments, index);
    }
    else
    {
        controller->replaceCommand(CMD_LINE, arguments, index);
    }
}

void LineDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);

        QString dxString = "";
        QString dyString = "";
        QString dzString = "";
        QString vString = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                dxString = arguments[i];
                break;
            case 1:
                dyString = arguments[i];
                break;
            case 2:
                dzString = arguments[i];
                break;
            case 3:
                vString = arguments[i];
                break;
            default:
                break;
            }
        }
        ui->dxLineEdit->setText(dxString);
        ui->dyLineEdit->setText(dyString);
        ui->dzLineEdit->setText(dzString);
        ui->velocityLineEdit->setText(vString);
    }
}

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
    QString dx = ui->dxLineEdit->text();
    QString dy = ui->dyLineEdit->text();
    QString dz = ui->dzLineEdit->text();
    QString v = ui->velocityLineEdit->text();

    if(dx.length() == 0)
    {
        dx = QString::number(0);
    }

    if(dy.length() == 0)
    {
        dy = QString::number(0);
    }

    if(dz.length() == 0)
    {
        dz = QString::number(0);
    }

    if(v.length() == 0)
    {
        v = QString::number(0);
    }

    QStringList arguments =
    {
        dx,
        dy,
        dz,
        v
    };

    if(!edit)
    {
        controller->insertCommand(CMD_LINE, arguments, index);
    }
    else
    {
        controller->updateCommand(arguments, index);
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

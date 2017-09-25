#include "arcdialog.h"
#include "ui_arcdialog.h"

ArcDialog::ArcDialog(MainWindowController* _controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::ArcDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_buttonBox_accepted()
{
    QStringList arguments =
    {
        ui->rLineEdit->text(),
        ui->alLineEdit->text(),
        ui->fiLneEdit->text(),
        ui->velocityLineEdit->text()
    };

    if(!edit)
    {
        controller->insertCommand(CMD_ARC, arguments, index);
    }
    else
    {
        controller->replaceCommand(CMD_ARC, arguments, index);
    }
}

void ArcDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);


        QString rString = "";
        QString alString = "";
        QString fiString = "";
        QString vString = "";
        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i) {
            case 0:
                rString = arguments[i];
                break;
            case 1:
                alString = arguments[i];
                break;
            case 2:
                fiString = arguments[i];
                break;
            case 3:
                vString = arguments[i];
                break;
            default:
                break;
            }
        }

        ui->rLineEdit->setText(rString);
        ui->alLineEdit->setText(alString);
        ui->fiLneEdit->setText(fiString);
        ui->velocityLineEdit->setText(vString);
    }
}

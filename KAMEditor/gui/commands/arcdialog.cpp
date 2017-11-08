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
    QString r = ui->rLineEdit->text();
    QString al = ui->alLineEdit->text();
    QString fi = ui->fiLneEdit->text();
    QString velocity = ui->velocityLineEdit->text();

    if(r.length() == 0)
    {
        r = QString::number(0);
    }

    if(al.length() == 0)
    {
        al = QString::number(0);
    }

    if(fi.length() == 0)
    {
        fi = QString::number(0);
    }

    if(velocity.length() == 0)
    {
        velocity = QString::number(0);
    }

    QStringList arguments =
    {
        r,
        al,
        fi,
        velocity
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

#include "smltttarcdialog.h"
#include "ui_smltttarcdialog.h"

SMLTTTArcDialog::SMLTTTArcDialog(MainWindowController *_controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLTTTArcDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

SMLTTTArcDialog::~SMLTTTArcDialog()
{
    delete ui;
}

void SMLTTTArcDialog::on_buttonBox_accepted()
{
    QString middlePointNumber = QString::number(ui->middlePointLineEdit->text().toUInt());
    QString endPointNumber = QString::number(ui->finishPointLineEdit->text().toUInt());
    QString v = QString::number(ui->velocityLineEdit->text().toDouble());

    QStringList arguments =
    {
        middlePointNumber,
        endPointNumber,
        v
    };

    if(!edit)
    {
        controller->insertCommand(CMD_TTTARC, arguments, index);
    }
    else
    {
        controller->updateCommand(arguments, index);
    }
}

void SMLTTTArcDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString middlePointSring = "";
        QString endPointString = "";
        QString velocityString = QString::number(0);

        for(int i = 0; i < arguments.size(); i++)
        {
            switch (i)
            {
            case 0:
                middlePointSring = arguments[i];
                break;
            case 1:
                endPointString = arguments[i];
                break;
            case 2:
                velocityString = arguments[i];
            default:
                break;
            }
        }

        ui->middlePointLineEdit->setText(middlePointSring);
        ui->finishPointLineEdit->setText(endPointString);
        ui->velocityLineEdit->setText(velocityString);
    }
}

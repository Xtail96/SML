#include "smlcommentdialog.h"
#include "ui_smlcommentdialog.h"

SMLCommentDialog::SMLCommentDialog(MainWindowController* _controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::SMLCommentDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

SMLCommentDialog::~SMLCommentDialog()
{
    delete ui;
}

void SMLCommentDialog::on_buttonBox_accepted()
{
    QStringList arguments =
    {
        ui->commentTextLineEdit->text()
    };

    if(!edit)
    {
        controller->insertCommand(CMD_COMMENT, arguments, index);
    }
    else
    {
        controller->updateCommand(arguments, index);
    }
}

void SMLCommentDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString comment = arguments[0];
        ui->commentTextLineEdit->setText(comment);
    }
}

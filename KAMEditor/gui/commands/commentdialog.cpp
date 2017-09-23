#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(MainWindowController* _controller, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::CommentDialog),
    controller(_controller),
    index(_index),
    edit(_edit)
{
    ui->setupUi(this);
    fillFields();
}

CommentDialog::~CommentDialog()
{
    delete ui;
}

void CommentDialog::on_buttonBox_accepted()
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
        controller->replaceCommand(CMD_COMMENT, arguments, index);
    }
}

void CommentDialog::fillFields()
{
    if(edit)
    {
        QStringList arguments = controller->getCommandArguments(index);
        QString comment = arguments[0];
        ui->commentTextLineEdit->setText(comment);
    }
}

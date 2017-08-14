#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(CommandsManager* _commandsManager, size_t _index, QWidget *parent, bool _edit) :
    QDialog(parent),
    ui(new Ui::CommentDialog),
    commandsManager(_commandsManager),
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
    std::string comment = ui->commentTextLineEdit->text().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Comment(comment));

    if(edit)
    {
        commandsManager->operator [](index) = cmd;
    }
    else
    {
        commandsManager->insertCommand(index, cmd);
    }
}

void CommentDialog::fillFields()
{
    if(edit)
    {
        std::shared_ptr<Command> currentCommand = commandsManager->operator [](index);
        QStringList arguments = currentCommand->getArguments();
        QString comment = arguments[0];
        ui->commentTextLineEdit->setText(comment);
    }
}

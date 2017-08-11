#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(CommandsManager* _commandsManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommentDialog),
    commandsManager(_commandsManager)
{
    ui->setupUi(this);
}

CommentDialog::~CommentDialog()
{
    delete ui;
}

void CommentDialog::on_buttonBox_accepted()
{
    std::string comment = ui->commentTextLineEdit->text().toStdString();
    std::shared_ptr<Command> cmd = std::shared_ptr<Command> (new Comment(comment));
    commandsManager->addCommand(cmd);
}

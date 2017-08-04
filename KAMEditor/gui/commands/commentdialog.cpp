#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(MachineTool *_machineTool, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommentDialog),
    machineTool(_machineTool)
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
    machineTool->getCommandsManager()->addCommand(cmd);
}

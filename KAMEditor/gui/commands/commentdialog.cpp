#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommentDialog)
{
    ui->setupUi(this);

    std::vector<QLineEdit*> fields =
    {
         ui->comment_text_lineEdit
    };
    fillFields(fields);
}

CommentDialog::~CommentDialog()
{
    delete ui;
}

void CommentDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_COMMENT;


    cmd.commandColor = "#2E8B57";
    std::string commentText = ui->comment_text_lineEdit->text().toStdString();
    cmd.args.push_back(commentText);
    setCommandArguments(cmd);
}

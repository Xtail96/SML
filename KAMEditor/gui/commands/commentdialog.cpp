#include "commentdialog.h"
#include "ui_commentdialog.h"

CommentDialog::CommentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CommentDialog)
{
    ui->setupUi(this);

    QFile description("./description/comment.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->comment_description_textEdit->setHtml(content);
    description.close();
    CommandInterpreter& instance = CommandInterpreter::Instance();
    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
        unsigned int current_command_number = instance.getSelectedCommand();
        std::vector <Command> commands = instance.getCommands();
        std::vector <std::string> current_command_arguments;
        current_command_arguments = commands[current_command_number].args;
        ui->comment_text_lineEdit->setText(QString::fromStdString(current_command_arguments[0]));
    }
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

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();

    bool editSignal = instance.getSelectedCommandEditSignal();
    if(editSignal)
    {
       instance.editCommandsArguments(cmd.args, selected_command);
       instance.setSelectedCommandEditSignal(false);
    }
    else
    {
        instance.addCommand(cmd, selected_command);
    }
}

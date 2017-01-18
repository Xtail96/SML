#include "cycledialog.h"
#include "ui_cycledialog.h"

CycleDialog::CycleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CycleDialog)
{
    ui->setupUi(this);
    QFile description("./description/for.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->cycle_textEdit_description->setHtml(content);
    description.close();
}

CycleDialog::~CycleDialog()
{
    delete ui;
}

void CycleDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_FOR;

    cmd.commandColor = "#999900";

    int amount = ui->cycle_amount_lineEdit->text().toInt();
    cmd.args = {
     std::to_string(amount),
    };
    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}

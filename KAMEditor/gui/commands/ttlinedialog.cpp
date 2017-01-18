#include "ttlinedialog.h"
#include "ui_ttlinedialog.h"

TTLineDialog::TTLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTLineDialog)
{
    ui->setupUi(this);
    QFile description("./description/ttline.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->ttline_textEdit_description->setHtml(content);
    description.close();
}

TTLineDialog::~TTLineDialog()
{
    delete ui;
}

void TTLineDialog::on_buttonBox_accepted()
{
    Command cmd;
    cmd.id = CMD_TTLINE;

    int startPoint = ui->ttline_start_point_lineEdit->text().toInt();
    int finishPoint = ui->ttline_finish_point_lineEdit->text().toInt();
    int velocity = ui->ttline_velocity_lineEdit->text().toInt();

    cmd.commandColor = "#333";

    cmd.args = {
     std::to_string(startPoint),
     std::to_string(finishPoint),
     std::to_string(velocity),
    };

    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int selected_command = instance.getSelectedCommand();
    instance.addCommand(cmd, selected_command);
}

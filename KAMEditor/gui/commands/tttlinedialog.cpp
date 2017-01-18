#include "tttlinedialog.h"
#include "ui_tttlinedialog.h"

TTTLineDialog::TTTLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TTTLineDialog)
{
    ui->setupUi(this);
    QFile description("./description/tttline.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->tttline_textEdit_description->setHtml(content);
    description.close();
}

TTTLineDialog::~TTTLineDialog()
{
    delete ui;
}

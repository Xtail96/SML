#include "arc2dialog.h"
#include "ui_arc2dialog.h"

Arc2Dialog::Arc2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arc2Dialog)
{
    ui->setupUi(this);
    QFile description("./description/arc2.html");
    if(!description.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", description.errorString());
    }
    QTextStream in(&description);
    QString content = in.readAll();
    ui->arc2_textEdit_description->setHtml(content);
    description.close();
}

Arc2Dialog::~Arc2Dialog()
{
    delete ui;
}

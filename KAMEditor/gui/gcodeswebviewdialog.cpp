#include "gcodeswebviewdialog.h"
#include "ui_gcodeswebviewdialog.h"

GCodesWebViewDialog::GCodesWebViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GCodesWebViewDialog)
{
    ui->setupUi(this);
}

GCodesWebViewDialog::~GCodesWebViewDialog()
{
    delete ui;
}

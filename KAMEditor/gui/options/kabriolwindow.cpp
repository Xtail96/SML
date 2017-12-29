#include "kabriolwindow.h"
#include "ui_kabriolwindow.h"

KabriolWindow::KabriolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KabriolWindow)
{
    ui->setupUi(this);
}

KabriolWindow::~KabriolWindow()
{
    delete ui;
}

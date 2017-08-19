#include "lubricationsystemwindow.h"
#include "ui_lubricationsystemwindow.h"

LubricationSystemWindow::LubricationSystemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LubricationSystemWindow)
{
    ui->setupUi(this);
}

LubricationSystemWindow::~LubricationSystemWindow()
{
    delete ui;
}

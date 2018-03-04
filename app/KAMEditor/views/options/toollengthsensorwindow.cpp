#include "toollengthsensorwindow.h"
#include "ui_toollengthsensorwindow.h"

ToolLengthSensorWindow::ToolLengthSensorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ToolLengthSensorWindow)
{
    ui->setupUi(this);
}

ToolLengthSensorWindow::~ToolLengthSensorWindow()
{
    delete ui;
}

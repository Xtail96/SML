#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("Ready"));
    QMainWindow::showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

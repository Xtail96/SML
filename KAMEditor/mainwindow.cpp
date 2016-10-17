#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("Ready"));
    QMainWindow::showMaximized();


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(100);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}


void MainWindow::update()
{
    update_coordinates();

}


void MainWindow::update_coordinates()
{
    MachineTool<Point4D> &i = MachineTool<Point4D>::Instance();

    Point4D current = i.getCurrentCoordinates();
    Point4D base = i.getBaseCoordinates();
    Point4D park = i.getParkCoordinates();


    ui->listWidget_currentCoordinates->item(0)->setText("X: " + QString::number(current.x));
    ui->listWidget_currentCoordinates->item(1)->setText("Y: " + QString::number(current.y));
    ui->listWidget_currentCoordinates->item(2)->setText("Z: " + QString::number(current.z));

    ui->listWidget_baseCoordinates->item(0)->setText("X: " + QString::number(base.x));
    ui->listWidget_baseCoordinates->item(1)->setText("Y: " + QString::number(base.y));
    ui->listWidget_baseCoordinates->item(2)->setText("Z: " + QString::number(base.z));

    ui->listWidget_parkCoordinates->item(0)->setText("X: " + QString::number(park.x));
    ui->listWidget_parkCoordinates->item(1)->setText("Y: " + QString::number(park.y));
    ui->listWidget_parkCoordinates->item(2)->setText("Z: " + QString::number(park.z));
}

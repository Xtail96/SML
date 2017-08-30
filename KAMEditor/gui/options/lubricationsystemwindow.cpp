#include "lubricationsystemwindow.h"
#include "ui_lubricationsystemwindow.h"

LubricationSystemWindow::LubricationSystemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LubricationSystemWindow),
    generalLubricationTimer(new QTimer(this)),
    stepLubriactionTimer(new QTimer(this))
{
    ui->setupUi(this);

    connect(generalLubricationTimer, SIGNAL(timeout()), this, SLOT(stop()));
    generalLubricationTimer->setInterval(16000);

    connect(stepLubriactionTimer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
    stepLubriactionTimer->setInterval(160);

    ui->lubricateProgressBar->setValue(0);
}

LubricationSystemWindow::~LubricationSystemWindow()
{
    delete ui;

    delete generalLubricationTimer;

    delete stepLubriactionTimer;
}

void LubricationSystemWindow::on_lubricatePushButton_clicked()
{
    // включить САС

    generalLubricationTimer->start();
    stepLubriactionTimer->start();

    ui->lubricateProgressBar->setValue(0);
}

void LubricationSystemWindow::stop()
{
    // выключить САС
    generalLubricationTimer->stop();

    stepLubriactionTimer->stop();

    ui->lubricateProgressBar->setValue(100);

    ui->lastLubricationDateTimeEdit->setDate(QDate::currentDate());
}

void LubricationSystemWindow::updateProgressBar()
{
    ui->lubricateProgressBar->setValue(ui->lubricateProgressBar->value() + 1);
}

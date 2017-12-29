#include "lubricationsystemwindow.h"
#include "ui_lubricationsystemwindow.h"

LubricationSystemWindow::LubricationSystemWindow(DevicesManager *_devicesManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LubricationSystemWindow),
    devicesManager(_devicesManager),
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
    switchLubricationSystem();

    generalLubricationTimer->start();
    stepLubriactionTimer->start();
    ui->lubricateProgressBar->setValue(0);

    ui->statusLineEdit->setText("Смазка начата!");
}

void LubricationSystemWindow::stop()
{
    // выключить САС
    switchLubricationSystem();

    generalLubricationTimer->stop();

    stepLubriactionTimer->stop();

    ui->lubricateProgressBar->setValue(100);

    ui->lastLubricationDateTimeEdit->setDate(QDate::currentDate());
    ui->lastLubricationDateTimeEdit->setTime(QTime::currentTime());

    ui->statusLineEdit->setText("Смазка завершена!");
}

void LubricationSystemWindow::updateProgressBar()
{
    ui->statusLineEdit->setText("Идет смазка!");
    ui->lubricateProgressBar->setValue(ui->lubricateProgressBar->value() + 1);
}

void LubricationSystemWindow::switchLubricationSystem()
{
    std::string deviceName = "САС";
    try
    {
        Device &device = devicesManager->findDevice(deviceName);
        byte_array data = devicesManager->getSwitchDeviceData(device, !device.getCurrentState());
#ifdef Q_OS_WIN
        /*try
        {
            u1Manager->getU1()->sendData(data);
        }
        catch(std::runtime_error e)
        {
            QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        }*/
#endif
        device.setCurrentState(!device.getCurrentState());
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

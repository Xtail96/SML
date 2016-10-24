#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage(tr("Ready"));
    QMainWindow::showMaximized();


    // таймер обновления окна координат
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
    update_battery_status();
}


void MainWindow::update_coordinates()
{
    BaseMachineTool &i = BaseMachineTool::Instance();

    Vector3D current = i.getCurrentCoordinates();
    Vector3D base = i.getBaseCoordinates();
    Vector3D park = i.getParkCoordinates();


    ui->listWidget_currentCoordinates->item(0)->setText("X: " + QString::number(current.x, 'f', 3));
    ui->listWidget_currentCoordinates->item(1)->setText("Y: " + QString::number(current.y, 'f', 3));
    ui->listWidget_currentCoordinates->item(2)->setText("Z: " + QString::number(current.z, 'f', 3));

    ui->listWidget_baseCoordinates->item(0)->setText("X: " + QString::number(base.x, 'f', 3));
    ui->listWidget_baseCoordinates->item(1)->setText("Y: " + QString::number(base.y, 'f', 3));
    ui->listWidget_baseCoordinates->item(2)->setText("Z: " + QString::number(base.z, 'f', 3));

    ui->listWidget_parkCoordinates->item(0)->setText("X: " + QString::number(park.x, 'f', 3));
    ui->listWidget_parkCoordinates->item(1)->setText("Y: " + QString::number(park.y, 'f', 3));
    ui->listWidget_parkCoordinates->item(2)->setText("Z: " + QString::number(park.z, 'f', 3));
}

void MainWindow::update_battery_status()
{
    SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);

    if ((status.BatteryLifePercent < 0) || (status.BatteryLifePercent > 100))
        status.BatteryLifePercent = 100;

    ui->battery_progress_bar->setValue(status.BatteryLifePercent);
}


void MainWindow::on_discrete_radio_button_1_clicked()
{

    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setMovementStep(0.01);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_2_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setMovementStep(0.1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_3_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setMovementStep(1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_4_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setMovementStep(10);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_5_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setMovementStep(0);

    setMovementButtonsRepeatState(true);
}


void MainWindow::on_movement_x_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {1, 0, 0}) );
}


void MainWindow::on_movement_x_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {-1, 0, 0}) );
}


void MainWindow::on_movement_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {0, 1, 0}) );
}

void MainWindow::on_movement_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {0, -1, 0}) );
}

void MainWindow::on_movement_x_negative_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {-1, 1, 0}) );
}


void MainWindow::on_movement_x_positive_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {1, 1, 0}) );
}

void MainWindow::on_movement_x_negative_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {-1, -1, 0}) );
}

void MainWindow::on_movement_x_positive_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {1, -1, 0}) );
}

void MainWindow::on_movement_z_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {0, 0, 1}) );
}

void MainWindow::on_movement_z_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.stepMove( Vector3D( {0, 0, -1}) );
}

void MainWindow::setMovementButtonsRepeatState(bool state)
{
    ui->movement_x_positive_button->setAutoRepeat(state);
    ui->movement_x_negative_button->setAutoRepeat(state);
    ui->movement_y_positive_button->setAutoRepeat(state);
    ui->movement_y_negative_button->setAutoRepeat(state);

    ui->movement_x_positive_y_positive_button->setAutoRepeat(state);
    ui->movement_x_positive_y_negative_button->setAutoRepeat(state);
    ui->movement_x_negative_y_positive_button->setAutoRepeat(state);
    ui->movement_x_positive_y_negative_button->setAutoRepeat(state);

    ui->movement_z_positive_button->setAutoRepeat(state);
    ui->movement_z_negative_button->setAutoRepeat(state);
}


void MainWindow::on_feedrate_scroll_bar_valueChanged(int value)
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setVelocity(value);

    ui->feedrate_lcd_number->display(value);
}

void MainWindow::on_rotations_scroll_bar_valueChanged(int value)
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    i.setRotation(value);

    ui->rotation_lcd_number->display(value);
}

void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

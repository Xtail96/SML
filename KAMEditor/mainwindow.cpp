#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->setStyleSheet("background-color: #000; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    // окно на весь экран
    QMainWindow::showMaximized();

    // таймер обновления окна координат
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(100);
    timer->start();

    sh = new QShortcut(QKeySequence("D"), ui->movement_x_positive_button);
    connect(sh, SIGNAL(activated()), this, SLOT(on_movement_x_positive_button_clicked()));
    sh->setAutoRepeat(false);

    // растянуть таблицу с координатами
    for (int i = 0; i < ui->points_table_widget->horizontalHeader()->count(); i++)
        ui->points_table_widget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;

    delete sh;
}


void MainWindow::update()
{
    update_coordinates();
    update_points();
    update_battery_status();
}


void MainWindow::update_coordinates()
{
    BaseMachineTool &i = BaseMachineTool::Instance();

    Vector3D current = i.getCurrentCoordinates();
    Vector3D base = i.getBaseCoordinates();
    Vector3D park = i.getParkCoordinates();

    std::vector<std::pair<QListWidget*, Vector3D>> widgets = {
        { ui->listWidget_currentCoordinates, current },
        { ui->listWidget_baseCoordinates, base },
        { ui->listWidget_parkCoordinates, park }
    };

    for (std::vector<std::pair<QListWidget*, Vector3D>>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        i->first->item(0)->setText("X: " + QString::number(i->second.x, 'f', 3));
        i->first->item(1)->setText("Y: " + QString::number(i->second.y, 'f', 3));
        i->first->item(2)->setText("Z: " + QString::number(i->second.z, 'f', 3));
        i->first->item(3)->setText("A: " + QString::number(i->second.a, 'f', 3));
    }
}

void MainWindow::update_points()
{

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
    BaseMachineTool::Instance().setMovementStep(0.01);

    setMovementButtonsRepeatState(false);

}


void MainWindow::on_discrete_radio_button_2_clicked()
{
    BaseMachineTool::Instance().setMovementStep(0.1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_3_clicked()
{
    BaseMachineTool::Instance().setMovementStep(1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_4_clicked()
{
    BaseMachineTool::Instance().setMovementStep(10);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_5_clicked()
{
    BaseMachineTool::Instance().setMovementStep(0);

    setMovementButtonsRepeatState(true);
}


void MainWindow::on_movement_x_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_x_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = -1;

    i.stepMove(v);
}


void MainWindow::on_movement_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_negative_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = -1;
    v.y = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_x_positive_y_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = 1;
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_negative_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = -1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_positive_y_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.x = 1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_z_positive_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.z = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_z_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.z = -1;

    i.stepMove(v);
}


void MainWindow::on_movement_a_posititve_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.a = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_a_negative_button_clicked()
{
    BaseMachineTool &i = BaseMachineTool::Instance();
    Vector3D v = Vector3D();
    v.a = -1;

    i.stepMove(v);
}


void MainWindow::setMovementButtonsRepeatState(bool state)
{
    std::vector<QPushButton*> buttons = {
        ui->movement_x_positive_button,
        ui->movement_x_negative_button,
        ui->movement_y_positive_button,
        ui->movement_y_negative_button,

        ui->movement_x_positive_y_positive_button,
        ui->movement_x_positive_y_negative_button,
        ui->movement_x_negative_y_positive_button,
        ui->movement_x_positive_y_negative_button,

        ui->movement_z_positive_button,
        ui->movement_z_negative_button,

        ui->movement_a_posititve_button,
        ui->movement_a_negative_button
    };

    for (std::vector<QPushButton*>::iterator i = buttons.begin(); i != buttons.end(); i++)
        (*i)->setAutoRepeat(state);
}

void MainWindow::on_feedrate_scroll_bar_valueChanged(int value)
{
    BaseMachineTool::Instance().setVelocity(value);

    ui->feedrate_lcd_number->display(value);
}

void MainWindow::on_rotations_scroll_bar_valueChanged(int value)
{
    BaseMachineTool::Instance().setRotation(value);

    ui->rotation_lcd_number->display(value);
}

void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

void MainWindow::on_point_amount_button_clicked()
{
    QMessageBox(QMessageBox::Information, "Количество точек", QString::number(ui->points_table_widget->rowCount())).exec();
}

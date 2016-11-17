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

    shortcutXNegativeButton = new QShortcut(QKeySequence("A"), ui->movement_x_negative_button);
    connect(shortcutXNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_x_negative_button_clicked()));
    shortcutXPositiveButton = new QShortcut(QKeySequence("D"), ui->movement_x_positive_button);
    connect(shortcutXPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_x_positive_button_clicked()));

    shortcutYNegativeButton = new QShortcut(QKeySequence("S"), ui->movement_y_negative_button);
    connect(shortcutYNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_y_negative_button_clicked()));
    shortcutYPositiveButton = new QShortcut(QKeySequence("W"), ui->movement_y_positive_button);
    connect(shortcutYPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_y_positive_button_clicked()));

    shortcutXNegativeYNegativeButton = new QShortcut(QKeySequence("Z"), ui->movement_x_negative_y_negative_button);
    connect(shortcutXNegativeYNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_x_negative_y_negative_button_clicked()));
    shortcutXNegativeYPositiveButton = new QShortcut(QKeySequence("Q"), ui->movement_x_negative_y_positive_button);
    connect(shortcutXNegativeYPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_x_negative_y_positive_button_clicked()));
    shortcutXPositiveYNegativeButton = new QShortcut(QKeySequence("X"), ui->movement_x_positive_y_negative_button);
    connect(shortcutXPositiveYNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_x_positive_y_negative_button_clicked()));
    shortcutXPositiveYPositiveButton = new QShortcut(QKeySequence("E"), ui->movement_x_positive_y_positive_button);
    connect(shortcutXPositiveYPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_x_positive_y_positive_button_clicked()));

    shortcutZNegativeButton = new QShortcut(QKeySequence("B"), ui->movement_z_negative_button);
    connect(shortcutZNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_z_negative_button_clicked()));
    shortcutZPositiveButton = new QShortcut(QKeySequence("T"), ui->movement_z_positive_button);
    connect(shortcutZPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_z_positive_button_clicked()));

    shortcutANegativeButton = new QShortcut(QKeySequence("N"), ui->movement_a_negative_button);
    connect(shortcutANegativeButton, SIGNAL(activated()), this, SLOT(on_movement_a_negative_button_clicked()));
    shortcutAPositiveButton = new QShortcut(QKeySequence("Y"), ui->movement_a_positive_button);
    connect(shortcutAPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_a_positive_button_clicked()));

    shortcutBNegativeButton = new QShortcut(QKeySequence("M"), ui->movement_b_negative_button);
    connect(shortcutBNegativeButton, SIGNAL(activated()), this, SLOT(on_movement_b_negative_button_clicked()));
    shortcutBPositiveButton = new QShortcut(QKeySequence("U"), ui->movement_b_positive_button);
    connect(shortcutBPositiveButton, SIGNAL(activated()), this, SLOT(on_movement_b_positive_button_clicked()));


    // растянуть таблицу с координатами
    for (int i = 0; i < ui->points_table_widget->horizontalHeader()->count(); i++)
        ui->points_table_widget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    // в таблице выделяется целиком вся строка
    ui->points_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;

    delete shortcutXNegativeButton;
    delete shortcutXPositiveButton;

    delete shortcutYNegativeButton;
    delete shortcutYPositiveButton;

    delete shortcutZNegativeButton;
    delete shortcutZPositiveButton;

    delete shortcutXNegativeYNegativeButton;
    delete shortcutXNegativeYPositiveButton;
    delete shortcutXPositiveYNegativeButton;
    delete shortcutXPositiveYPositiveButton;

    delete shortcutANegativeButton;
    delete shortcutAPositiveButton;

    delete shortcutBNegativeButton;
    delete shortcutBPositiveButton;
}


void MainWindow::update()
{
    update_coordinates();
    update_battery_status();
    update_kabriol_avaliability();
}


void MainWindow::update_coordinates()
{
    MachineTool &i = MachineTool::Instance();

    Vector current = i.getCurrentCoordinates();
    Vector base = i.getBaseCoordinates();
    Vector park = i.getParkCoordinates();

    std::vector<std::pair<QListWidget*, Vector>> widgets = {
        { ui->listWidget_currentCoordinates, current },
        { ui->listWidget_baseCoordinates, base },
        { ui->listWidget_parkCoordinates, park }
    };

    for (std::vector<std::pair<QListWidget*, Vector>>::iterator i = widgets.begin(); i != widgets.end(); i++)
    {
        i->first->item(0)->setText("X: " + QString::number(i->second.x, 'f', 3));
        i->first->item(1)->setText("Y: " + QString::number(i->second.y, 'f', 3));
        i->first->item(2)->setText("Z: " + QString::number(i->second.z, 'f', 3));
        i->first->item(3)->setText("A: " + QString::number(i->second.a, 'f', 3));
        i->first->item(4)->setText("B: " + QString::number(i->second.b, 'f', 3));
    }
}

void MainWindow::update_points()
{
    std::vector<Point> points = CommandInterpreter::Instance().getPoints();

    ui->points_table_widget->setRowCount(0);

    for (unsigned int i = 0; i < points.size(); i++)
    {
        ui->points_table_widget->insertRow(i);

        ui->points_table_widget->setItem(i, 0, new QTableWidgetItem( QString::number(points[i].x)) );
        ui->points_table_widget->setItem(i, 1, new QTableWidgetItem( QString::number(points[i].y)) );
        ui->points_table_widget->setItem(i, 2, new QTableWidgetItem( QString::number(points[i].z)) );
        ui->points_table_widget->setItem(i, 3, new QTableWidgetItem( QString::number(points[i].a)) );
        ui->points_table_widget->setItem(i, 4, new QTableWidgetItem( QString::number(points[i].b)) );
    }
}

void MainWindow::update_battery_status()
{
    SYSTEM_POWER_STATUS status;
    GetSystemPowerStatus(&status);

    if ((status.BatteryLifePercent < 0) || (status.BatteryLifePercent > 100))
        status.BatteryLifePercent = 100;

    ui->battery_progress_bar->setValue(status.BatteryLifePercent);
}


void MainWindow::update_kabriol_avaliability()
{
    if(ui->kabriol_off_radio_button->isChecked())
    {
        ui->movement_a_negative_button->setEnabled(false);
        ui->movement_a_positive_button->setEnabled(false);
    }
    if(ui->kabriol_servo_radio_button->isChecked() || ui->kabriol_on_radio_button->isChecked())
    {
        ui->movement_a_negative_button->setEnabled(true);
        ui->movement_a_positive_button->setEnabled(true);
    }
}

void MainWindow::on_discrete_radio_button_1_clicked()
{

    shortcutXNegativeButton->setAutoRepeat(false);
    shortcutXPositiveButton->setAutoRepeat(false);
    shortcutYNegativeButton->setAutoRepeat(false);
    shortcutYPositiveButton->setAutoRepeat(false);
    shortcutXNegativeYNegativeButton->setAutoRepeat(false);
    shortcutXNegativeYPositiveButton->setAutoRepeat(false);
    shortcutXPositiveYNegativeButton->setAutoRepeat(false);
    shortcutXPositiveYPositiveButton->setAutoRepeat(false);
    shortcutZNegativeButton->setAutoRepeat(false);
    shortcutZPositiveButton->setAutoRepeat(false);
    shortcutANegativeButton->setAutoRepeat(false);
    shortcutAPositiveButton->setAutoRepeat(false);
    shortcutBNegativeButton->setAutoRepeat(false);
    shortcutBPositiveButton->setAutoRepeat(false);

    MachineTool::Instance().setMovementStep(0.01);

    setMovementButtonsRepeatState(false);

}


void MainWindow::on_discrete_radio_button_2_clicked()
{

    shortcutXNegativeButton->setAutoRepeat(false);
    shortcutXPositiveButton->setAutoRepeat(false);
    shortcutYNegativeButton->setAutoRepeat(false);
    shortcutYPositiveButton->setAutoRepeat(false);
    shortcutXNegativeYNegativeButton->setAutoRepeat(false);
    shortcutXNegativeYPositiveButton->setAutoRepeat(false);
    shortcutXPositiveYNegativeButton->setAutoRepeat(false);
    shortcutXPositiveYPositiveButton->setAutoRepeat(false);
    shortcutZNegativeButton->setAutoRepeat(false);
    shortcutZPositiveButton->setAutoRepeat(false);
    shortcutANegativeButton->setAutoRepeat(false);
    shortcutAPositiveButton->setAutoRepeat(false);
    shortcutBNegativeButton->setAutoRepeat(false);
    shortcutBPositiveButton->setAutoRepeat(false);

    MachineTool::Instance().setMovementStep(0.1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_3_clicked()
{

    shortcutXNegativeButton->setAutoRepeat(false);
    shortcutXPositiveButton->setAutoRepeat(false);
    shortcutYNegativeButton->setAutoRepeat(false);
    shortcutYPositiveButton->setAutoRepeat(false);
    shortcutXNegativeYNegativeButton->setAutoRepeat(false);
    shortcutXNegativeYPositiveButton->setAutoRepeat(false);
    shortcutXPositiveYNegativeButton->setAutoRepeat(false);
    shortcutXPositiveYPositiveButton->setAutoRepeat(false);
    shortcutZNegativeButton->setAutoRepeat(false);
    shortcutZPositiveButton->setAutoRepeat(false);
    shortcutANegativeButton->setAutoRepeat(false);
    shortcutAPositiveButton->setAutoRepeat(false);
    shortcutBNegativeButton->setAutoRepeat(false);
    shortcutBPositiveButton->setAutoRepeat(false);

    MachineTool::Instance().setMovementStep(1);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_4_clicked()
{


    shortcutXNegativeButton->setAutoRepeat(false);
    shortcutXPositiveButton->setAutoRepeat(false);
    shortcutYNegativeButton->setAutoRepeat(false);
    shortcutYPositiveButton->setAutoRepeat(false);
    shortcutXNegativeYNegativeButton->setAutoRepeat(false);
    shortcutXNegativeYPositiveButton->setAutoRepeat(false);
    shortcutXPositiveYNegativeButton->setAutoRepeat(false);
    shortcutXPositiveYPositiveButton->setAutoRepeat(false);
    shortcutZNegativeButton->setAutoRepeat(false);
    shortcutZPositiveButton->setAutoRepeat(false);
    shortcutANegativeButton->setAutoRepeat(false);
    shortcutAPositiveButton->setAutoRepeat(false);
    shortcutBNegativeButton->setAutoRepeat(false);
    shortcutBPositiveButton->setAutoRepeat(false);

    MachineTool::Instance().setMovementStep(10);

    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_5_clicked()
{

    shortcutXNegativeButton->setAutoRepeat(true);
    shortcutXPositiveButton->setAutoRepeat(true);
    shortcutYNegativeButton->setAutoRepeat(true);
    shortcutYPositiveButton->setAutoRepeat(true);
    shortcutXNegativeYNegativeButton->setAutoRepeat(true);
    shortcutXNegativeYPositiveButton->setAutoRepeat(true);
    shortcutXPositiveYNegativeButton->setAutoRepeat(true);
    shortcutXPositiveYPositiveButton->setAutoRepeat(true);
    shortcutZNegativeButton->setAutoRepeat(true);
    shortcutZPositiveButton->setAutoRepeat(true);
    shortcutANegativeButton->setAutoRepeat(true);
    shortcutAPositiveButton->setAutoRepeat(true);
    shortcutBNegativeButton->setAutoRepeat(true);
    shortcutBPositiveButton->setAutoRepeat(true);

    MachineTool::Instance().setMovementStep(0);

    setMovementButtonsRepeatState(true);
}


void MainWindow::on_movement_x_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_x_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = -1;

    i.stepMove(v);
}


void MainWindow::on_movement_y_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_y_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_negative_y_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = -1;
    v.y = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_x_positive_y_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = 1;
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_negative_y_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = -1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_x_positive_y_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.x = 1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movement_z_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.z = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_z_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.z = -1;

    i.stepMove(v);
}


void MainWindow::on_movement_a_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.a = 1;

    i.stepMove(v);
}


void MainWindow::on_movement_a_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.a = -1;

    i.stepMove(v);
}




void MainWindow::on_movement_b_positive_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.b = 1;

    i.stepMove(v);
}

void MainWindow::on_movement_b_negative_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v.b = -1;

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

        ui->movement_a_positive_button,
        ui->movement_a_negative_button,

        ui->movement_b_positive_button,
        ui->movement_b_negative_button
    };

    for (std::vector<QPushButton*>::iterator i = buttons.begin(); i != buttons.end(); i++)
        (*i)->setAutoRepeat(state);
}

void MainWindow::on_feedrate_scroll_bar_valueChanged(int value)
{
    MachineTool::Instance().setVelocity(value);

    ui->feedrate_lcd_number->display(value);
}

void MainWindow::on_rotations_scroll_bar_valueChanged(int value)
{
    MachineTool::Instance().setRotation(value);

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

void MainWindow::on_park_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v = i.getCurrentCoordinates();
    i.setParkCoordinates(v);
}

void MainWindow::on_point_add_button_clicked()
{
    Point tmp = Point(1, 2, 3, 4, 5);
    CommandInterpreter::Instance().addPoint(tmp);

    update_points();
}

void MainWindow::on_point_delete_button_clicked()
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    QList<QTableWidgetItem*> selected = ui->points_table_widget->selectedItems();
    std::set<int> rows;

    for (QList<QTableWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++)
    {
        int row = ui->points_table_widget->row(*i);
        rows.insert(row);
    }

    for (std::set<int>::reverse_iterator i = rows.rbegin(); i != rows.rend(); i++)
    {
        instance.removePoint(*i);
    }

    update_points();
}

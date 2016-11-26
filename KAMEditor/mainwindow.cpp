#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // задаем горячие клавиши
    setupShortcuts();

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

    // растянуть таблицу с координатами
    for (int i = 0; i < ui->points_table_widget->horizontalHeader()->count(); i++)
    {
        ui->points_table_widget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->points_table_widget_2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // в таблице выделяется целиком вся строка
    ui->points_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->points_table_widget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;

    // удаляем горячие клавиши
    while (shortcuts.size() > 0)
    {
        delete shortcuts.back();
        shortcuts.pop_back();
    }
}


void MainWindow::setupShortcuts()
{
    std::vector<std::tuple <const char*, QPushButton*, const char*> > shortcutsMap = {
        std::make_tuple("A", ui->movement_x_negative_button, SLOT(on_movement_x_negative_button_clicked())),
        std::make_tuple("D", ui->movement_x_positive_button, SLOT(on_movement_x_positive_button_clicked())),
        std::make_tuple("S", ui->movement_y_negative_button, SLOT(on_movement_y_negative_button_clicked())),
        std::make_tuple("W", ui->movement_y_positive_button, SLOT(on_movement_y_positive_button_clicked())),
        std::make_tuple("Z", ui->movement_x_negative_y_negative_button, SLOT(on_movement_x_negative_y_negative_button_clicked())),
        std::make_tuple("Q", ui->movement_x_negative_y_positive_button, SLOT(on_movement_x_negative_y_positive_button_clicked())),
        std::make_tuple("X", ui->movement_x_positive_y_negative_button, SLOT(on_movement_x_positive_y_negative_button_clicked())),
        std::make_tuple("E", ui->movement_x_positive_y_positive_button, SLOT(on_movement_x_positive_y_positive_button_clicked())),
        std::make_tuple("B", ui->movement_z_negative_button, SLOT(on_movement_z_negative_button_clicked())),
        std::make_tuple("T", ui->movement_z_positive_button, SLOT(on_movement_z_positive_button_clicked())),
        std::make_tuple("N", ui->movement_a_negative_button, SLOT(on_movement_a_negative_button_clicked())),
        std::make_tuple("Y", ui->movement_a_positive_button, SLOT(on_movement_a_positive_button_clicked())),
        std::make_tuple("M", ui->movement_b_negative_button, SLOT(on_movement_b_negative_button_clicked())),
        std::make_tuple("U", ui->movement_b_positive_button, SLOT(on_movement_b_positive_button_clicked())),
    };

    for (auto i = shortcutsMap.begin(); i != shortcutsMap.end(); i++)
    {
        const char* shortcutKey = std::get<0>(*i);
        QPushButton* shortcutButton = std::get<1>(*i);
        const char* shortcutSlot = std::get<2>(*i);

        QShortcut* shortcut = new QShortcut(QKeySequence(shortcutKey), shortcutButton);
        connect(shortcut, SIGNAL(activated()), this, shortcutSlot);

        shortcuts.push_back(shortcut);
    }
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

    for (auto i = widgets.begin(); i != widgets.end(); i++)
    {
        i->first->item(0)->setText("X: " + QString::number(i->second.x, 'f', 3) + " мм");
        i->first->item(1)->setText("Y: " + QString::number(i->second.y, 'f', 3) + " мм");
        i->first->item(2)->setText("Z: " + QString::number(i->second.z, 'f', 3) + " мм");
        i->first->item(3)->setText("A: " + QString::number(i->second.a, 'f', 3) + " град.");
        i->first->item(4)->setText("B: " + QString::number(i->second.b, 'f', 3) + " мм");
    }
}

void MainWindow::update_points()
{
    std::vector<Point> points = CommandInterpreter::Instance().getPoints();

    std::vector<QTableWidget*> tables = { ui->points_table_widget, ui->points_table_widget_2 };

    for (auto table = tables.begin(); table != tables.end(); table++)
    {
        (*table)->setRowCount(0);

        for (unsigned int i = 0; i < points.size(); i++)
        {
            (*table)->insertRow(i);

            (*table)->setItem(i, 0, new QTableWidgetItem( QString::number(points[i].x)) );
            (*table)->setItem(i, 1, new QTableWidgetItem( QString::number(points[i].y)) );
            (*table)->setItem(i, 2, new QTableWidgetItem( QString::number(points[i].z)) );
            (*table)->setItem(i, 3, new QTableWidgetItem( QString::number(points[i].a)) );
            (*table)->setItem(i, 4, new QTableWidgetItem( QString::number(points[i].b)) );
        }
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

void MainWindow::disableMovementButtonsShortcuts()
{
    setMovementButtonsShortcutsState(false);
}

void MainWindow::enableMovementButtonsShortcuts()
{
    setMovementButtonsShortcutsState(true);
}

void MainWindow::setMovementButtonsShortcutsState(bool state)
{
    for (auto i = shortcuts.begin(); i != shortcuts.end(); i++)
        (*i)->setAutoRepeat(state);
}

void MainWindow::setMovementButtonsRepeatState(bool state)
{
    std::vector<QPushButton*> movementButtons = {
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

    for (std::vector<QPushButton*>::iterator i = movementButtons.begin(); i != movementButtons.end(); i++)
        (*i)->setAutoRepeat(state);
}


void MainWindow::on_discrete_radio_button_1_clicked()
{
    MachineTool::Instance().setMovementStep(0.01);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_2_clicked()
{
    MachineTool::Instance().setMovementStep(0.1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_3_clicked()
{
    MachineTool::Instance().setMovementStep(1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_4_clicked()
{
    MachineTool::Instance().setMovementStep(10);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}


void MainWindow::on_discrete_radio_button_5_clicked()
{
    MachineTool::Instance().setMovementStep(0);

    enableMovementButtonsShortcuts();
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
    v = i.getBaseCoordinates();
    i.setParkCoordinates(v);
}


void MainWindow::on_zero_button_clicked()
{
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v = i.getBaseCoordinates();
    i.setNewZeroCoordinates(v);
}


void MainWindow::on_point_add_button_clicked()
{
    Point tmp = Point(rand(), rand(), rand(), rand(), rand());
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

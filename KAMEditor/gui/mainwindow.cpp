#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // задаем горячие клавиши
    setupShortcuts();

    setupEditorShortcuts();


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

    ui->points_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->points_table_widget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

    while(editorShortcuts.size() > 0)
    {
        delete editorShortcuts.back();
        editorShortcuts.pop_back();
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

void MainWindow::setupEditorShortcuts()
{
    std::vector<std::pair<const char*, const char*> > editorShortcutsMap = {
        std::make_pair("Ctrl+W", SLOT(addLineCommand())),
        std::make_pair("Backspace", SLOT(deleteCommand())),
    };

    for (unsigned int i = 0; i < editorShortcutsMap.size(); i++)
    {
        const char* shortcutKey = editorShortcutsMap[i].first;
        const char* shortcutSlot = editorShortcutsMap[i].second;

        QShortcut* shortcut = new QShortcut(this);
        shortcut->setKey(QKeySequence(shortcutKey));
        connect(shortcut, SIGNAL(activated()), this, shortcutSlot);

        editorShortcuts.push_back(shortcut);
    }
}


void MainWindow::update()
{
    update_coordinates();
    update_battery_status();
    update_kabriol_avaliability();
    update_base_status();
}

void MainWindow::deleteCommand()
{
    if(ui->editor_tab->isVisible())
    {
        if(ui->sml_editor_tab->isVisible())
        {
            CommandInterpreter &commands = CommandInterpreter::Instance();
            QItemSelectionModel *select = ui->sml_editor_treeWidget->selectionModel();
            if(select->hasSelection())
            {
                unsigned int current_row = select->currentIndex().row();
                commands.deleteSelectedCommands(current_row);
            }
            update_commands();
        }
    }
}

void MainWindow::addLineCommand()
{
    if(ui->editor_tab->isVisible())
    {
        if(ui->sml_editor_tab->isVisible())
        {
            LineDialog(this).exec();
        }
    }
    update_commands();
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
    std::vector<Point> points = PointsManager::Instance().getPoints();

    std::vector<QTableWidget*> tables = { ui->points_table_widget, ui->points_table_widget_2 };

    // проходим по каждой таблице
    for (auto table = tables.begin(); table != tables.end(); table++)
    {
        // очищаем текущую таблицу
        (*table)->setRowCount(0);

        // проходим по всем точкам
        for (unsigned int i = 0; i < points.size(); i++)
        {
            // координаты текущей точки
            std::vector<double> pointCoordinates = { points[i].x, points[i].y, points[i].z, points[i].a, points[i].b };

            // добавляем строку в таблицу для текущей точки
            (*table)->insertRow(i);

            // отображаем координаты текущей точки
            for (unsigned int coordinate = 0; coordinate < pointCoordinates.size(); coordinate++)
                (*table)->setItem(i, coordinate, new QTableWidgetItem( QString::number(pointCoordinates[coordinate])) );
        }
    }
}


void MainWindow::update_commands()
{
    std::vector<Command> commands = CommandInterpreter::Instance().getCommands();

    QTreeWidget*  editorField = ui->sml_editor_treeWidget;

    // очищаем текущую таблицу
    editorField->clear();

    editorField->setColumnCount(3);

    QList<QTreeWidgetItem *> items;

    // проходим по всем точкам
    for (unsigned int i = 0; i < commands.size(); i++)
    {

        // добавляем строку в таблицу для текущей точки
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(i+1));

        QString commandColor = QString::fromStdString(commands[i].commandColor);
        item->setTextColor(1, QColor(commandColor));
        item->setTextColor(2, QColor(commandColor));

        item->setText(1, QString::fromStdString(getNameByCommand(commands[i].id)));
        std::string s;
        for(int j = 0; j<commands[i].args.size();j++)
        {
            s+=commands[i].args[j]+"; ";
        }
        item->setText(2, QString::fromStdString(s));

        items.append(item);
    }

    editorField->insertTopLevelItems(0, items);
}

void MainWindow::update_battery_status()
{
    #ifdef Q_OS_WIN
        SYSTEM_POWER_STATUS status;
        GetSystemPowerStatus(&status);

        if ((status.BatteryLifePercent < 0) || (status.BatteryLifePercent > 100))
        status.BatteryLifePercent = 100;

        ui->battery_progress_bar->setValue(status.BatteryLifePercent);
    #endif
    #ifdef Q_OS_OSX
        ui->battery_progress_bar->setValue(100);
    #endif
}

void MainWindow::update_base_status()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getIsBased())
    {
       ui->edges_contol_check_box->setEnabled(true);
       ui->edges_contol_check_box->setChecked(true);

       ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #2E8B57");
       ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #2E8B57");
       ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #2E8B57");
    }
    else
    {
        ui->edges_contol_check_box->setChecked(false);
        ui->edges_contol_check_box->setEnabled(false);

        ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #B22222");
        ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #B22222");
        ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #B22222");
    }
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
    AddPointDialog* addPoint = new AddPointDialog(this);
    addPoint->exec();
    delete addPoint;
    //Point tmp = Point(rand(), rand(), rand(), rand(), rand());
    //CommandInterpreter::Instance().addPoint(tmp);
    update_points();
}

void MainWindow::on_point_delete_button_clicked()
{
    PointsManager& instance = PointsManager::Instance();
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

void MainWindow::on_point_cursor_button_clicked()
{
    MouseToSelectionPointDialog* toPoint = new MouseToSelectionPointDialog(this);
    toPoint->exec();
    delete toPoint;

    PointsManager& point_table = PointsManager::Instance();

    unsigned int point_to_select = point_table.getSelectedPoint();
    ui->points_table_widget->selectRow(point_to_select);
}

void MainWindow::on_point_edit_button_clicked()
{
    QItemSelectionModel *select = ui->points_table_widget->selectionModel();
    if(select->hasSelection())
    {
        //select->selectedRows();

        int current_row = select->currentIndex().row();

        PointsManager& point_table = PointsManager::Instance();
        point_table.setSelectedPoint(current_row);

        EditPointDialog* editPoint = new EditPointDialog(this);
        editPoint->exec();
        delete editPoint;
        update_points();
    }
    else
    {
         QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка не выбрана")).exec();
    }
}


void MainWindow::on_point_copy_button_clicked()
{
    PointsManager& instance = PointsManager::Instance();
    std::vector<Point> points = instance.getPoints();

    QList<QTableWidgetItem*> selected = ui->points_table_widget->selectedItems();
    std::set<int> rows;

    for (QList<QTableWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++)
    {
        int row = ui->points_table_widget->row(*i);
        rows.insert(row);
    }

    for (std::set<int>::iterator i = rows.begin(); i != rows.end(); i++)
    {
        instance.addPoint(points[*i]);
    }

    update_points();

}



void MainWindow::on_commands_tools_listWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();

    QItemSelectionModel *select = ui->sml_editor_treeWidget->selectionModel();
    if(select->hasSelection())
    {
        unsigned int current_row =  select->currentIndex().row();
        instance.setSelectedCommand(current_row);
    }
    else
    {
        std::vector<Command> commands = instance.getCommands();
        unsigned int selected;
        if(commands.size()>0)
        {
           selected = commands.size();
        }
        else
        {
            selected = 0;
        }
        instance.setSelectedCommand(selected);
    }

    int row = index.row();

    QString name = ui->commands_tools_listWidget->item(row)->text() ;

    COMMAND cmd = getCommandByName(name.toStdString());

    switch (cmd)
    {
        case CMD_LINE:
        {
            LineDialog(this).exec();
            break;
        }

        case CMD_TTLINE:
        {
            TTLineDialog(this).exec();
            break;
        }

        case CMD_TTTLINE:
        {
            TTTLineDialog(this).exec();
            break;
        }

        case CMD_ARC:
        {
            ArcDialog(this).exec();
            break;
        }

        case CMD_ARC2:
        {
            Arc2Dialog(this).exec();
            break;
        }

        case CMD_ROTATE:
        {
            RotateDialog(this).exec();
            break;
        }

        case CMD_FOR:
        {
            CycleDialog(this).exec();
            break;
        }

        case CMD_ENDFOR:
        {
            Command command;
            command.id = CMD_ENDFOR;
            command.commandColor = "#999900";

            std::string endfor = "";
            command.args = {
                endfor
            };

            CommandInterpreter& instance = CommandInterpreter::Instance();
            unsigned int selected_command = instance.getSelectedCommand();
            instance.addCommand(command, selected_command);
            break;
        }

        case CMD_LABEL:
        {
            LabelDialog(this).exec();
            break;
        }
    }
    update_commands();
}


void MainWindow::on_commands_adjustment_listWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();

    QItemSelectionModel *select = ui->sml_editor_treeWidget->selectionModel();
    if(select->hasSelection())
    {
        unsigned int current_row =  select->currentIndex().row();
        instance.setSelectedCommand(current_row);
    }
    else
    {
        std::vector<Command> commands = instance.getCommands();
        unsigned int selected;
        if(commands.size()>0)
        {
           selected = commands.size();
        }
        else
        {
            selected = 0;
        }
        instance.setSelectedCommand(selected);
    }

    int row = index.row();

    QString name = ui->commands_adjustment_listWidget->item(row)->text() ;

    COMMAND cmd = getCommandByName(name.toStdString());
    switch (cmd)
    {
        case CMD_ZERO:
        {
            Command command;
            command.id = CMD_ZERO;

            command.commandColor = "#000099";

            std::string setZero = "";
            command.args = {
                setZero
            };

            CommandInterpreter& instance = CommandInterpreter::Instance();
            unsigned int selected_command = instance.getSelectedCommand();
            instance.addCommand(command, selected_command);
            break;
        }
        case CMD_END:
        {
            Command command;
            command.id = CMD_END;

            command.commandColor = "#660099";

            std::string endProgramm = "";
            command.args = {
                endProgramm
            };

            CommandInterpreter& instance = CommandInterpreter::Instance();
            unsigned int selected_command = instance.getSelectedCommand();
            instance.addCommand(command, selected_command);
            break;
        }
        case CMD_ON:
        {
            OnDialog(this).exec();
            break;
        }

        case CMD_OFF:
        {
            OffDialog(this).exec();
            break;
        }
    }
    update_commands();
}

void MainWindow::on_to_base_button_clicked()
{
    MachineTool& instance = MachineTool::Instance();
    instance.setIsBased(true);
    update_base_status();
}

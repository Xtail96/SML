 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // задаем габариты станка
    setupDimensions();
    // задаем направления движения осей станка
    setupDirections();
    // задаем настройки кинематики
    setupKinematicsSettings();
    // задаем характеристики электроники
    setUpElectricalSettings();

    // задаем горячие клавиши
    setupShortcuts();


    QTreeWidget*  editorField = ui->sml_editor_treeWidget;
    editorField->setTreePosition(1);

    setupEditorShortcuts();

    hightlighter = new GCodesSyntaxHighlighter(this);
    hightlighter->setDocument(ui->gcodes_editor_textEdit->document());
    hightlighter->setPattern();


    update_edges_control_status();

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


    ui->spindle_enable_pushButton->setEnabled(false);
    ui->spindle_enable_pushButton->setStyleSheet("margin: 1px");

    ui->length_sensor_button->setEnabled(false);
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

    connect(ui->open_button, SIGNAL(clicked()), this, SLOT(on_open_action_triggered()));
    connect(ui->numofdots_button, SIGNAL(clicked()), this, SLOT(on_point_amount_button_clicked()));
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
        QTreeWidget* smlEditorField = ui->sml_editor_treeWidget;
        if(smlEditorField->isVisible())
        {
            CommandInterpreter &commands = CommandInterpreter::Instance();
            QItemSelectionModel *select = smlEditorField->selectionModel();
            if(select->hasSelection())
            {
                QList<QTreeWidgetItem *> selected_items = smlEditorField->selectedItems();
                std::vector<int> vector_numbers;
                vector_numbers.reserve(selected_items.size());
                for(int i = 0; i < selected_items.size(); i++)
                {
                    int current_vector_number = std::stoi(selected_items[i]->text(0).toStdString()) - 1;
                    vector_numbers.push_back(current_vector_number);
                }
                std::sort(vector_numbers.begin(), vector_numbers.end());
                for(unsigned int i = 0; i < vector_numbers.size(); i++)
                {
                    int current_row = vector_numbers[0];
                    commands.deleteSelectedCommands(current_row);
                }
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
        i->first->item(3)->setText("A: " + QString::number(i->second.a, 'f', 3) + " град");
        i->first->item(4)->setText("B: " + QString::number(i->second.b, 'f', 3) + " град");
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

    // очищаем поле
    editorField->clear();

    editorField->setColumnCount(3);

    QList<QTreeWidgetItem *> items;

    QTreeWidgetItem* previousParent = nullptr;

    // проходим по всем командам
    for (unsigned int i = 0; i < commands.size(); i++)
    {

        // добавляем строку для текущей команды
        QTreeWidgetItem* item;
        switch(commands[i].id)
        {
            case CMD_FOR:
            {
                item = new QTreeWidgetItem(previousParent);
                previousParent = item;
                break;
            }
            case CMD_ENDFOR:
            {
                if(previousParent)
                {
                    previousParent = previousParent->parent();
                }
                item = new QTreeWidgetItem(previousParent);
                break;
            }
            case CMD_PROC:
            {
                item = new QTreeWidgetItem(previousParent);
                previousParent = item;
                break;
            }
            case CMD_RETURN:
            {
                if(previousParent)
                {
                    previousParent = previousParent->parent();
                }
                item = new QTreeWidgetItem(previousParent);
                break;
            }
            default:
            {
                item = new QTreeWidgetItem(previousParent);
                break;
            }
        }



        item->setText(0, QString::number(i+1));
        QString commandColor = QString::fromStdString(commands[i].commandColor);
        item->setTextColor(1, QColor(commandColor));
        item->setTextColor(2, QColor(commandColor));

        item->setText(1, QString::fromStdString(getNameByCommand(commands[i].id)));
        std::string s;
        for(unsigned int j = 0; j<commands[i].args.size();j++)
        {
            s+=commands[i].args[j]+"; ";
        }
        item->setText(2, QString::fromStdString(s));
        items.append(item);
    }
    editorField->insertTopLevelItems(0, items);
    editorField->expandAll();
    for(int i=0; i<2; i++)
    {
        editorField->resizeColumnToContents(i);
    }
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
    if(instance.getBaseStatus())
    {
       ui->edges_contol_check_box->setEnabled(true);
       ui->length_sensor_button->setEnabled(true);
    }
    else
    {
        ui->edges_contol_check_box->setEnabled(false); 
        ui->length_sensor_button->setEnabled(false);
    }
}


void MainWindow::update_kabriol_avaliability()
{
    if(ui->kabriol_off_radio_button->isChecked())
    {
        ui->movement_b_negative_button->setEnabled(false);
        ui->movement_b_positive_button->setEnabled(false);
    }
    if(ui->kabriol_servo_radio_button->isChecked() || ui->kabriol_on_radio_button->isChecked())
    {
        ui->movement_b_negative_button->setEnabled(true);
        ui->movement_b_positive_button->setEnabled(true);
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
        ui->movement_x_negative_y_negative_button,

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

void MainWindow::on_points_table_widget_doubleClicked(const QModelIndex &index)
{
    QItemSelectionModel *select = ui->points_table_widget->selectionModel();
    if(select->hasSelection())
    {
        int current_row = index.row();

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
    std::vector<Command> commands = instance.getCommands();

    QTreeWidget* editorField = ui->sml_editor_treeWidget;

    QItemSelectionModel *select = editorField->selectionModel();
    if(!select->hasSelection())
    {
        unsigned int current_row = commands.size();
        instance.setSelectedCommand(current_row);
    }


    int row = index.row();

    QString name = ui->commands_tools_listWidget->item(row)->text();

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

        case CMD_TTZARC:
        {
            TTZArcDialog(this).exec();
            break;
        }


        case CMD_TTTARC:
        {
            TTTArcDialog(this).exec();
            break;
        }

        case CMD_SPLINE:
        {
            SplineDialog(this).exec();
            break;
        }

        case CMD_TTTTSPLINE:
        {
            TTTTSplineDialog(this).exec();
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

        case CMD_GOTO:
        {
            GoToDialog(this).exec();
            break;
        }
        case CMD_PROC:
        {
            ProcDialog(this).exec();
            break;
        }
        case CMD_RETURN:
        {
            Command command;
            command.id = CMD_RETURN;
            //command.commandColor = "#2f4f4f";
            command.commandColor = "#4682B4";

            std::string endProc = "";
            command.args = {
                endProc
            };

            CommandInterpreter& instance = CommandInterpreter::Instance();
            unsigned int selected_command = instance.getSelectedCommand();
            instance.addCommand(command, selected_command);
            break;
        }
        case CMD_CALL:
        {
            CallProcDialog(this).exec();
            break;
        }
        case CMD_SCALEX:
        {
            ScaleDialog(this).exec();
            break;
        }
        case CMD_COMMENT:
        {
            CommentDialog(this).exec();
            break;
        }
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
        case CMD_SPEED:
        {
            VelocityDialog(this).exec();
            break;
        }
        case CMD_PAUSE:
        {
            PauseDialog(this).exec();
            break;
        }
        case CMD_STOP:
        {
            StopDialog(this).exec();
            break;
        }
        default:
        {
            QMessageBox().critical(this, "Undefined command", "Error: find undefined command");
            break;
        }
    }
    update_commands();
}

void MainWindow::on_sml_editor_treeWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& commandInterpreter = CommandInterpreter::Instance();
    commandInterpreter.setSelectedCommandEditSignal(true);
    QString name = ui->sml_editor_treeWidget->currentItem()->text(1);
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
            commandInterpreter.setSelectedCommandEditSignal(false);
            break;
        }

        case CMD_LABEL:
        {
            LabelDialog(this).exec();
            break;
        }
        case CMD_GOTO:
        {
            GoToDialog(this).exec();
            break;
        }
        case CMD_PROC:
        {
            ProcDialog(this).exec();
            break;
        }
        case CMD_RETURN:
        {
            commandInterpreter.setSelectedCommandEditSignal(false);
            break;
        }
        case CMD_CALL:
        {
            CallProcDialog(this).exec();
            break;
        }
        case CMD_ZERO:
        {
            commandInterpreter.setSelectedCommandEditSignal(false);
            break;
        }
        case CMD_END:
        {
            commandInterpreter.setSelectedCommandEditSignal(false);
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
        case CMD_SCALEX:
        {
            ScaleDialog(this).exec();
            break;
        }
        case CMD_SPEED:
        {
            VelocityDialog(this).exec();
            break;
        }
        case CMD_PAUSE:
        {
            PauseDialog(this).exec();
            break;
        }
        case CMD_STOP:
        {
            StopDialog(this).exec();
            break;
        }
        case CMD_COMMENT:
        {
            CommentDialog(this).exec();
            break;
        }
        case CMD_TTZARC:
        {
            TTZArcDialog(this).exec();
            break;
        }
        case CMD_TTTARC:
        {
            TTTArcDialog(this).exec();
            break;
        }
        case CMD_SPLINE:
        {
            SplineDialog(this).exec();
            break;
        }
        case CMD_TTTTSPLINE:
        {
            TTTTSplineDialog(this).exec();
            break;
        }
        default:
        {
            QMessageBox().critical(this, "Undefined command", "Error: find undefined command");
            break;
        }
    }
    update_commands();
}

void MainWindow::on_sml_editor_treeWidget_clicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int current_row;
    setSelectedCommandVectorNumber(current_row);
    instance.setSelectedCommand(current_row);
}


void MainWindow::setSelectedCommandVectorNumber(unsigned int& current_row)
{
    //получаем значение из нулевого столбца выделнного элемента
    QTreeWidget* editorField = ui->sml_editor_treeWidget;
    QList<QTreeWidgetItem *> selected_items = editorField->selectedItems();
    QTreeWidgetItem* item = selected_items[0];
    std::string s  = item->text(0).toStdString();
    current_row = std::stoi(s) - 1;
}

void MainWindow::update_edges_control_status()
{
    MachineTool& instance = MachineTool::Instance();
    if(instance.getBaseStatus())
    {
        if(instance.getEdgesControlEnable())
        {
            ui->edges_contol_check_box->setChecked(true);
            ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #2E8B57");
            ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #2E8B57");
            ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #2E8B57");
        }
        else
        {
            ui->edges_contol_check_box->setChecked(false);
            ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #B22222");
            ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #B22222");
            ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #B22222");
        }
    }
    else
    {
        ui->edges_contol_check_box->setEnabled(false);
        ui->edges_contol_check_box->setChecked(false);
        ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #B22222");
        ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #B22222");
        ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #B22222");
    }
}

void MainWindow::on_to_base_button_clicked()
{
    MachineTool& instance = MachineTool::Instance();
    instance.setBaseStatus(true);
    instance.setEdgesControlEnable(true);
    update_base_status();
    update_edges_control_status();
}

void MainWindow::on_edges_contol_check_box_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getEdgesControlEnable())
    {
       instance.setEdgesControlEnable(false);
       ui->edges_contol_check_box->setChecked(false);
       ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #B22222");
       ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #B22222");
       ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #B22222");
    }
    else
    {
        instance.setEdgesControlEnable(true);
        ui->edges_contol_check_box->setChecked(true);

        ui->listWidget_currentCoordinates->setStyleSheet("border: 2px solid #2E8B57");
        ui->listWidget_baseCoordinates->setStyleSheet("border: 2px solid #2E8B57");
        ui->listWidget_parkCoordinates->setStyleSheet("border: 2px solid #2E8B57");
    }
}

void MainWindow::on_spindle_enable_pushButton_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getSpindleEnable())
    {
        //ui->spindle_enable_pushButton->setStyleSheet("");
        ui->spindle_enable_pushButton->setStyleSheet("background-color: #2E8B57; color: #fff; border: 1px solid #000");
        ui->spindle_enable_pushButton->setText("F1 - Включить шпиндель");
        instance.setSpindleEnable(false);
    }
    else
    {
        ui->spindle_enable_pushButton->setStyleSheet("background-color: #B22222; color: #fff; border: 1px solid #000");
        ui->spindle_enable_pushButton->setText("F1 - Выключить шпиндель");
        instance.setSpindleEnable(true);
    }
}

void MainWindow::on_mill_warming_pushButton_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(!instance.getSpindleWarmUp())
    {
        instance.setSpindleWarmUp(true);
        ui->spindle_enable_pushButton->setEnabled(true);
        ui->spindle_enable_pushButton->setStyleSheet("background-color: #2E8B57; color: #fff; border: 1px solid #000");
    }
    else
    {

    }
}

void MainWindow::on_open_action_triggered()
{
    QString path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt, *.7kam");
    QFile inputFile(path);
    if(!inputFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", inputFile.errorString());
    }
    QTextStream in(&inputFile);
    QString content = in.readAll();
    inputFile.close();

    parse7kamToSml(content);
    ui->gcodes_editor_textEdit->setPlainText(content);
}

void MainWindow::parse7kamToSml(QString &tmp)
{
    ui->sml_editor_treeWidget->clear();
    std::string commandsList = tmp.toStdString();
    while(commandsList.length() != 0)
    {
        parse7kamToSmlStep(commandsList);
    }
}

void MainWindow::parse7kamToSmlStep(std::string &tmp)
{
    CommandInterpreter &commands = CommandInterpreter::Instance();
    Command newCommand;
    int position = 0;

    // получаем id команды
    int commandId = std::stoi(tmp);
    switch(commandId)
    {
    case 0:
    {
        newCommand.id = CMD_TTLINE;
        newCommand.commandColor = "#333";
        break;
    }
    case 1:
    {
        newCommand.id = CMD_TTARC;
        newCommand.commandColor = "#333";
        break;
    }
    case 4:
    {
        newCommand.id = CMD_LINE;
        newCommand.commandColor = "#333";
        break;
    }
    default:
        newCommand.id = CMD_UNDEFINED;
        //position = tmp.length();
        break;
    }

    // получаем аргументы команды
    std::string commandArguments;
    bool space = false;
    for(auto i : tmp)
    {
        position++;
        // откидываем id
        if(i == ' ')
        {
            space = true;
        }
        else
        {

            // если id уже откинут
            if(space)
            {
                // если не символ переноса строки
                if(i != '\n' && i != '\r')
                {
                    commandArguments += i;
                }
                else
                {
                    // если текущий символ - символ переноса строки, выделены все аргументы
                    break;
                }
            }
        }
    }
    tmp.erase(tmp.begin(), tmp.begin() + position);
    setCommandArguments(commandArguments, newCommand);
    unsigned int selectedCommand = commands.getSelectedCommand();
    commands.addCommand(newCommand, selectedCommand);
    commands.setSelectedCommand(selectedCommand + 1);
    update_commands();
}
 void MainWindow::setCommandArguments(std::string s, Command &command)
 {
     eraseSpecialSymbols(s);
     std::string argument;
     for(unsigned int i = 0; i < s.length(); i++)
     {
         //выделить числа и слова, состоящие из латинских букв из строки
         if(i < s.length() - 1)
         {
             if(s[i] != ',')
             {
                 argument += s[i];
             }
             else
             {
                 command.args.push_back(argument);
                 argument = "";
             }
         }
         else
         {
            argument += s[i];
            command.args.push_back(argument);
            argument = "";
         }
     }
 }


void MainWindow::eraseSpecialSymbols(std::string &s)
{
    std::string tmp = "";
    bool skip = false;
    for(auto it : s)
    {
        if(it == '^')
        {
            skip = true;
        }
        else
        {
            if(!skip)
            {
                tmp += it;
            }
            else
            {
                skip = false;
            }
        }
    }
    s = tmp;
}


void MainWindow::editSettingsField(QLineEdit *qle)
{
    qle->setReadOnly(false);
    qle->setStyleSheet("border: 1px solid #4682B4; font-size: 14pt");
}
void MainWindow::applySettingsField(QLineEdit *qle)
{
    qle->setReadOnly(true);
    qle->setStyleSheet("font-size: 14pt");
}

std::vector<QLineEdit *> MainWindow::makeQLineEditVector(int tmp)
{
    switch (tmp)
    {
        case 1:
        {
            std::vector<QLineEdit*> mechanicalSettingsVector =
            {
                ui->x_dimension_lineEdit,
                ui->y_dimension_lineEdit,
                ui->z_dimension_lineEdit,
                ui->a_dimension_lineEdit,
                ui->b_dimension_lineEdit,

                ui->x_axis_jerk_lineEdit,
                ui->x_axis_acceleration_lineEdit,
                ui->x_axis_velocity_lineEdit,
                ui->x_axis_channel_lineEdit,
                ui->x_axis_basing_velocity_lineEdit,

                ui->y_axis_jerk_lineEdit,
                ui->y_axis_acceleration_lineEdit,
                ui->y_axis_velocity_lineEdit,
                ui->y_axis_channel_lineEdit,
                ui->y_axis_basing_velocity_lineEdit,

                ui->z_axis_jerk_lineEdit,
                ui->z_axis_acceleration_lineEdit,
                ui->z_axis_velocity_lineEdit,
                ui->z_axis_channel_lineEdit,
                ui->z_axis_basing_velocity_lineEdit,

                ui->a_axis_jerk_lineEdit,
                ui->a_axis_acceleration_lineEdit,
                ui->a_axis_velocity_lineEdit,
                ui->a_axis_channel_lineEdit,
                ui->a_axis_basing_velocity_lineEdit,

                ui->b_axis_jerk_lineEdit,
                ui->b_axis_acceleration_lineEdit,
                ui->b_axis_velocity_lineEdit,
                ui->b_axis_channel_lineEdit,
                ui->b_axis_basing_velocity_lineEdit,

                ui->critical_axis_lineEdit,
                ui->buffer_size_lineEdit,
                ui->collinearity_tolerance_lineEdit,
                ui->maximum_devation_lineEdit,
                ui->smoothing_angle_lineEdit,

                ui->zero_level_sensor_lineEdit,
                ui->tool_length_sensor_lineEdit,
                ui->velocity_from_sensor_lineEdit,
                ui->minimum_sensor_finding_velocity_lineEdit
            };
            return mechanicalSettingsVector;
            break;
        }
        case 2:
        {
            std::vector<QLineEdit*> electricalSettingsFieldVector =
            {
                ui->x_axis_step_lineEdit,
                ui->y_axis_step_lineEdit,
                ui->z_axis_step_lineEdit,
                ui->a_axis_step_lineEdit,
                ui->b_axis_step_lineEdit,

                ui->x_axis_mm_lineEdit,
                ui->y_axis_mm_lineEdit,
                ui->z_axis_mm_lineEdit,
                ui->a_axis_mm_lineEdit,
                ui->b_axis_mm_lineEdit
            };
            return electricalSettingsFieldVector;
            break;
        }
        default:
        {
            std::vector<QLineEdit*> _vector;
            return _vector;
            break;
        }
    }
}

std::vector<QCheckBox*> MainWindow::makeQCheckBoxVector(int tmp)
{
    switch(tmp)
    {
        case 1:
        {
            std::vector<QCheckBox*> invertAxisVector =
            {
                ui->x_axis_invert_checkBox,
                ui->y_axis_invert_checkBox,
                ui->z_axis_invert_checkBox,
                ui->a_axis_invert_checkBox,
                ui->b_axis_invert_checkBox
            };
            return invertAxisVector;
            break;
        }
        case 2:
        {
            std::vector<QCheckBox*> externalDevicesVector =
            {
                ui->mill_checkBox,
                ui->kabriol_checkBox,
                ui->lubrication_system_checkBox,
                ui->tool_change_checkBox,
                ui->laser_checkBox,
                ui->wacuum_table_checkBox,
                ui->tool_length_sensor_checkBox
            };
            return externalDevicesVector;
            break;
        }
        default:
        {
           std::vector<QCheckBox*> _vector;
           return _vector;
           break;
        }
    }
}

void MainWindow::on_change_mechanics_settings_pushButton_clicked()
{
    std::vector<QLineEdit*> mechanicalSettings = makeQLineEditVector(1);
    for (auto i : mechanicalSettings)
    {
        editSettingsField(i);
    }

    std::vector<QCheckBox*> invertAxis = makeQCheckBoxVector(1);
    for(auto i : invertAxis)
    {
        i->setEnabled(true);
        i->setCheckable(true);
    }
}


void MainWindow::on_cancel_mechanical_settings_pushButton_clicked()
{
    dimensionsRecovery();
    directionsRecovery();
    std::vector<QLineEdit*> mechanicalSettings = makeQLineEditVector(1);
    for (auto i : mechanicalSettings)
    {
        applySettingsField(i);
    } 
    std::vector<QCheckBox*> invertAxis = makeQCheckBoxVector(1);
    for(auto i : invertAxis)
    {
        i->setEnabled(false);
    }
}

void MainWindow::on_apply_mechanics_settings_pushButton_clicked()
{
    setupDimensions();
    setupDirections();
    setupKinematicsSettings();

    std::vector<QLineEdit*> mechanicalSettings = makeQLineEditVector(1);
    for (auto i : mechanicalSettings)
    {
        applySettingsField(i);
    }
    std::vector<QCheckBox*> invertAxis = makeQCheckBoxVector(1);
    for(auto i : invertAxis)
    {
        i->setEnabled(false);
    }
}

void MainWindow::on_change_elecrical_settings_pushButton_clicked()
{    
    std::vector<QLineEdit*> electricalSettings = makeQLineEditVector(2);
    for (auto i : electricalSettings)
    {
        editSettingsField(i);
    }

    std::vector<QCheckBox*> externalDevices = makeQCheckBoxVector(2);
    for(auto i : externalDevices)
    {
        i->setEnabled(true);
        i->setCheckable(true);
    }
}

void MainWindow::setUpElectricalSettings()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v =
    {
        ui->x_axis_step_lineEdit->text().toDouble(),
        ui->y_axis_step_lineEdit->text().toDouble(),
        ui->z_axis_step_lineEdit->text().toDouble(),
        ui->a_axis_step_lineEdit->text().toDouble(),
        ui->b_axis_step_lineEdit->text().toDouble(),
    };
    instance.setDistanceByOneStep(v);

    v.x = ui->x_axis_mm_lineEdit->text().toDouble();
    v.y = ui->y_axis_mm_lineEdit->text().toDouble();
    v.z = ui->z_axis_mm_lineEdit->text().toDouble();
    v.a = ui->a_axis_mm_lineEdit->text().toDouble();
    v.b = ui->b_axis_mm_lineEdit->text().toDouble();
    instance.setStepQuantityByOneMm(v);

    std::map<std::string, bool> m =
    {
        {"mill", ui->mill_checkBox->isChecked()},
        {"kabriol", ui->kabriol_checkBox->isChecked()},
        {"lubrication_system", ui->lubrication_system_checkBox->isChecked()},
        {"tool_change", ui->tool_change_checkBox->isChecked()},
        {"laser", ui->laser_checkBox->isChecked()},
        {"wacuum_table", ui->wacuum_table_checkBox->isChecked()},
        {"tool_length_sensor", ui->tool_length_sensor_checkBox->isChecked()}
    };
    instance.setExternalDevices(m);
}

void MainWindow::on_apply_electrical_settings_pushButton_clicked()
{

    setUpElectricalSettings();
    std::vector<QLineEdit*> electricalSettings = makeQLineEditVector(2);
    for (auto i : electricalSettings)
    {
        applySettingsField(i);
    }
    std::vector<QCheckBox*> externalDevices = makeQCheckBoxVector(2);
    for(auto i : externalDevices)
    {
        i->setEnabled(false);
    }
}
void MainWindow::electricialSettingsRecovery()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v = instance.getDistanceByOneStep();
    ui->x_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
    ui->y_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
    ui->z_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
    ui->a_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
    ui->b_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));

    v = instance.getStepQuantityByOneMm();
    ui->x_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
    ui->y_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
    ui->z_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
    ui->a_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
    ui->b_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));

    std::map<std::string, bool> m = instance.getExternalDevices();
    if(m["mill"])
    {
        ui->mill_checkBox->setChecked(true);
    }
    else
    {
        ui->mill_checkBox->setChecked(false);
    }

    if(m["kabriol"])
    {
        ui->kabriol_checkBox->setChecked(true);
    }
    else
    {
        ui->kabriol_checkBox->setChecked(false);
    }

    if(m["lubrication_system"])
    {
        ui->lubrication_system_checkBox->setChecked(true);
    }
    else
    {
        ui->lubrication_system_checkBox->setChecked(false);
    }

    if(m["tool_change"])
    {
        ui->tool_change_checkBox->setChecked(true);
    }
    else
    {
        ui->tool_change_checkBox->setChecked(false);
    }

    if(m["laser"])
    {
        ui->laser_checkBox->setChecked(true);
    }
    else
    {
        ui->laser_checkBox->setChecked(false);
    }

    if(m["wacuum_table"])
    {
        ui->wacuum_table_checkBox->setChecked(true);
    }
    else
    {
        ui->wacuum_table_checkBox->setChecked(false);
    }
    if(m["tool_length_sensor"])
    {
        ui->tool_length_sensor_checkBox->setChecked(true);
    }
    else
    {
        ui->tool_length_sensor_checkBox->setChecked(false);
    }
}

void MainWindow::on_cancel_electrical_settings_pushButton_clicked()
{
    electricialSettingsRecovery();

    std::vector<QLineEdit*> electricalSettings = makeQLineEditVector(2);
    for (auto i : electricalSettings)
    {
        applySettingsField(i);
    }
    std::vector<QCheckBox*> externalDevices = makeQCheckBoxVector(2);
    for(auto i : externalDevices)
    {
        i->setEnabled(false);
    }
}

void MainWindow::setupDimensions()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v;
    v.x = ui->x_dimension_lineEdit->text().toDouble();
    v.y = ui->y_dimension_lineEdit->text().toDouble();
    v.z = ui->z_dimension_lineEdit->text().toDouble();
    v.a = ui->a_dimension_lineEdit->text().toDouble();
    v.b = ui->b_dimension_lineEdit->text().toDouble();
    instance.setDimensions(v);
}

void MainWindow::setupDirections()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v;
    v.x = ui->x_axis_invert_checkBox->isChecked();
    v.y = ui->y_axis_invert_checkBox->isChecked();
    v.z = ui->z_axis_invert_checkBox->isChecked();
    v.a = ui->a_axis_invert_checkBox->isChecked();
    v.b = ui->b_axis_invert_checkBox->isChecked();
    instance.setDirections(v);
}

void MainWindow::setupKinematicsSettings()
{
    MachineTool &instance = MachineTool::Instance();
    AxisKFlopSettings axis;
    axis.jerk = ui->x_axis_jerk_lineEdit->text().toDouble();
    axis.acceleration = ui->x_axis_acceleration_lineEdit->text().toDouble();
    axis.velocity = ui->x_axis_velocity_lineEdit->text().toDouble();
    axis.channel = ui->x_axis_channel_lineEdit->text().toDouble();
    axis.basingVelocity = ui->x_axis_basing_velocity_lineEdit->text().toDouble();
    std::vector<AxisKFlopSettings> tmp;
    tmp.push_back(axis);
    axis.jerk = ui->y_axis_jerk_lineEdit->text().toDouble();
    axis.acceleration = ui->y_axis_acceleration_lineEdit->text().toDouble();
    axis.velocity = ui->y_axis_velocity_lineEdit->text().toDouble();
    axis.channel = ui->y_axis_channel_lineEdit->text().toDouble();
    axis.basingVelocity = ui->x_axis_basing_velocity_lineEdit->text().toDouble();
    tmp.push_back(axis);
    axis.jerk = ui->z_axis_jerk_lineEdit->text().toDouble();
    axis.acceleration = ui->z_axis_acceleration_lineEdit->text().toDouble();
    axis.velocity = ui->z_axis_velocity_lineEdit->text().toDouble();
    axis.channel = ui->z_axis_channel_lineEdit->text().toDouble();
    axis.basingVelocity = ui->x_axis_basing_velocity_lineEdit->text().toDouble();
    tmp.push_back(axis);
    axis.jerk = ui->a_axis_jerk_lineEdit->text().toDouble();
    axis.acceleration = ui->a_axis_acceleration_lineEdit->text().toDouble();
    axis.velocity = ui->a_axis_velocity_lineEdit->text().toDouble();
    axis.channel = ui->a_axis_channel_lineEdit->text().toDouble();
    axis.basingVelocity = ui->a_axis_basing_velocity_lineEdit->text().toDouble();
    tmp.push_back(axis);
    axis.jerk = ui->b_axis_jerk_lineEdit->text().toDouble();
    axis.acceleration = ui->b_axis_acceleration_lineEdit->text().toDouble();
    axis.velocity = ui->b_axis_velocity_lineEdit->text().toDouble();
    axis.channel = ui->b_axis_channel_lineEdit->text().toDouble();
    axis.basingVelocity = ui->b_axis_basing_velocity_lineEdit->text().toDouble();
    tmp.push_back(axis);
    instance.setAxisKFlopSettings(tmp);
}

void MainWindow::dimensionsRecovery()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v = instance.getDimensions();
    ui->x_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
    ui->y_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
    ui->z_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
    ui->a_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
    ui->b_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));
}
void MainWindow::directionsRecovery()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v = instance.getDirections();

    std::vector<QCheckBox*> mechanicalCheckBoxes = makeQCheckBoxVector(1);
    for(auto i : mechanicalCheckBoxes)
    {
        i->setChecked(false);
    }

    if(v.x == 1)
    {
        ui->x_axis_invert_checkBox->setChecked(true);
    }
    if(v.y == 1)
    {
        ui->y_axis_invert_checkBox->setChecked(true);
    }
    if(v.z == 1)
    {
        ui->z_axis_invert_checkBox->setChecked(true);
    }
    if(v.a == 1)
    {
        ui->a_axis_invert_checkBox->setChecked(true);
    }
    if(v.b == 1)
    {
        ui->b_axis_invert_checkBox->setChecked(true);
    }
}

void MainWindow::kinematicsSettingsRecovery()
{
    MachineTool &instance = MachineTool::Instance();
    std::vector<AxisKFlopSettings> tmp = instance.getAxisKFlopSettings();
}


void MainWindow::on_gcodes_editor_textEdit_textChanged()
{
    QString text = ui->gcodes_editor_textEdit->toPlainText();
}

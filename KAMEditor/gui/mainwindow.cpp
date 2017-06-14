#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // окно на весь экран
    QMainWindow::showMaximized();

    // считываем настройки станка из файла и сохраняем их в структуру данных
    setupSettings();

    // отображаем считанные данные о настройках осей в интерфейсе
    updateSettingsField();

    // задаем горячие клавиши
    setupShortcuts();

    QTreeWidget*  editorField = ui->smlEditorTreeWidget;
    editorField->setTreePosition(1);

    setupEditorShortcuts();

    hightlighter = new GCodesSyntaxHighlighter(this);
    hightlighter->setDocument(ui->gcodesEditorTextEdit->document());
    hightlighter->setPattern();


    updateEdgesControlStatus();

    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    // таймер обновления окна координат
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(100);
    timer->start();

    // растянуть таблицу с координатами
    for (int i = 0; i < ui->pointsTableWidget->horizontalHeader()->count(); i++)
    {
        ui->pointsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->pointsTableWidget_2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // в таблице выделяется целиком вся строка
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointsTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->spindelEnablePushButton->setEnabled(false);
    ui->spindelEnablePushButton->setStyleSheet("margin: 1px");

    ui->toolLengthSensorPushButton->setEnabled(false);

    CommandInterpreter::Instance().addCommand(new CArc(1, 0, M_PI/2), 0);
    CommandInterpreter::Instance().addCommand(new Line(0.1, 0.2, 0), 1);
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

void MainWindow::setupSettings()
{
    MachineTool &instance = MachineTool::Instance();
    instance.addMachineToolAxis(5);
}

void MainWindow::updateSettingsField()
{
    MachineTool &instance = MachineTool::Instance();
    std::vector<Axis> axisVector = instance.getMachineToolAxis();
    for(auto it : axisVector)
    {
        chooseAxisSettingsItems(it);
    }
}

void MainWindow::chooseAxisSettingsItems(const Axis &axis)
{
    std::string axisName = axis.getName();
    int key = axisNames.getKeyByName(axisName);
    std::vector<QLineEdit *> axisSettingsQLineEdits;
    QCheckBox *isAxisInvertedCheckBox;
    switch (key) {
    case 0:
    {   axisSettingsQLineEdits =
        {
            ui->xAxisAccelerationLineEdit,
            ui->xAxisBasingVelocityLineEdit,
            ui->xAxisChannelLineEdit,
            ui->xAxisJerkLineEdit,
            ui->xAxisStepLineEdit,
            ui->xAxisVelocityLineEdit,
            ui->xDimensionLineEdit,
        };
        isAxisInvertedCheckBox = ui->xAxisInvertCheckBox;
        break;
    }
    case 1:
    {   axisSettingsQLineEdits =
        {
            ui->yAxisAccelerationLineEdit,
            ui->yAxisBasingVelocityLineEdit,
            ui->yAxisChannelLineEdit,
            ui->yAxisJerkLineEdit,
            ui->yAxisStepLineEdit,
            ui->yAxisVelocityLineEdit,
            ui->yDimensionLineEdit,
        };
        isAxisInvertedCheckBox = ui->yAxisInvertCheckBox;
        break;
    }
    case 2:
    {   axisSettingsQLineEdits =
        {
            ui->zAxisAccelerationLineEdit,
            ui->zAxisBasingVelocityLineEdit,
            ui->zAxisChannelLineEdit,
            ui->zAxisJerkLineEdit,
            ui->zAxisStepLineEdit,
            ui->zAxisVelocityLineEdit,
            ui->zDimensionLineEdit,
        };
        isAxisInvertedCheckBox = ui->zAxisInvertCheckBox;
        break;
    }
    case 3:
    {   axisSettingsQLineEdits =
        {
            ui->aAxisAccelerationLineEdit,
            ui->aAxisBasingVelocityLineEdit,
            ui->aAxisChannelLineEdit,
            ui->aAxisJerkLineEdit,
            ui->aAxisStepLineEdit,
            ui->aAxisVelocityLineEdit,
            ui->aDimensionLineEdit,
        };
        isAxisInvertedCheckBox = ui->aAxisInvertCheckBox;
        break;
    }
    case 4:
    {   axisSettingsQLineEdits =
        {
            ui->bAxisAccelerationLineEdit,
            ui->bAxisBasingVelocityLineEdit,
            ui->bAxisChannelLineEdit,
            ui->bAxisJerkLineEdit,
            ui->bAxisStepLineEdit,
            ui->bAxisVelocityLineEdit,
            ui->bDimensionLineEdit,
        };
        isAxisInvertedCheckBox = ui->bAxisInvertCheckBox;
        break;
    }
    default:
    {
        break;
    }
    }

    if(axisSettingsQLineEdits.size() > 0)
    {
        displayAxisSettings(axisSettingsQLineEdits, isAxisInvertedCheckBox, axis);
    }
}

void MainWindow::displayAxisSettings(std::vector<QLineEdit *> axisSettingsFields, QCheckBox *isAxisInvert, const Axis &axis)
{
    QString qAxisAcceleration = QString::fromStdString(std::to_string(axis.getAcceleration()));
    QString qAxisBasingVelocity = QString::fromStdString(std::to_string(axis.getBasingVelocity()));
    QString qAxisChannel = QString::fromStdString(std::to_string(axis.getChannel()));
    QString qAxisJerk = QString::fromStdString(std::to_string(axis.getJerk()));
    QString qAxisStep = QString::fromStdString(std::to_string(axis.getStep()));
    QString qAxisVelocity = QString::fromStdString(std::to_string(axis.getVelocity()));
    QString qAxisLength = QString::fromStdString(std::to_string(axis.getLength()));

    axisSettingsFields[0]->setText(qAxisAcceleration);
    axisSettingsFields[1]->setText(qAxisBasingVelocity);
    axisSettingsFields[2]->setText(qAxisChannel);
    axisSettingsFields[3]->setText(qAxisJerk);
    axisSettingsFields[4]->setText(qAxisStep);
    axisSettingsFields[5]->setText(qAxisVelocity);
    axisSettingsFields[6]->setText(qAxisLength);

    isAxisInvert->setEnabled(true);
    isAxisInvert->setCheckable(true);
    axis.getInvertDirection() ? isAxisInvert->setChecked(true) : isAxisInvert->setChecked(false);
    isAxisInvert->setEnabled(false);
}

void MainWindow::setupShortcuts()
{
    std::vector<std::tuple <const char*, QPushButton*, const char*> > shortcutsMap = {
        std::make_tuple("A", ui->movementXNegativePushButton, SLOT(on_movementXNegativePushButton_clicked())),
        std::make_tuple("D", ui->movementXPositivePushButton, SLOT(on_movementXPositivePushButton_clicked())),
        std::make_tuple("S", ui->movementYNegativePushButton, SLOT(on_movementYNegativePushButton_clicked())),
        std::make_tuple("W", ui->movementYPositivePushButton, SLOT(on_movementYPositivePushButton_clicked())),
        std::make_tuple("Z", ui->movementXNegativeYNegativePushButton, SLOT(on_movementXNegativeYNegativePushButton_clicked())),
        std::make_tuple("Q", ui->movementXNegativeYPositivePushButton, SLOT(on_movementXNegativeYPositivePushButton_clicked())),
        std::make_tuple("X", ui->movementXPositiveYNegativePushButton, SLOT(on_movementXPositiveYNegativePushButton_clicked())),
        std::make_tuple("E", ui->movementXPositiveYPositivePushButton, SLOT(on_movementXPositiveYPositivePushButton_clicked())),
        std::make_tuple("B", ui->movementZNegativePushButton, SLOT(on_movementZNegativePushButton_clicked())),
        std::make_tuple("T", ui->movementZPositivePushButton, SLOT(on_movementZPositivePushButton_clicked())),
        std::make_tuple("N", ui->movementANegativePushButton, SLOT(on_movementANegativePushButton_clicked())),
        std::make_tuple("Y", ui->movementAPositivePushButton, SLOT(on_movementAPositivePushButton_clicked())),
        std::make_tuple("M", ui->movementBNegativePushButton, SLOT(on_movementBNegativePushButton_clicked())),
        std::make_tuple("U", ui->movementBPositivePushButton, SLOT(on_movementBPositivePushButton_clicked())),
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
        std::make_pair("Backspace", SLOT(deleteSelectedCommands())),
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

    connect(ui->openFilePushButton, SIGNAL(clicked()), this, SLOT(on_open_action_triggered()));
    connect(ui->numOfDotsPushButton, SIGNAL(clicked()), this, SLOT(on_pointsAmountPushButton_clicked()));
}

void MainWindow::update()
{
    updateCoordinates();
    updateBatteryStatus();
    updateKabriolAvaliability();
    updateBaseStatus();
}

void MainWindow::deleteSelectedCommands()
{
    if(ui->editorTab->isVisible())
    {
        QTreeWidget* smlEditorField = ui->smlEditorTreeWidget;
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

                unsigned int begin = vector_numbers[0];
                unsigned int end = vector_numbers[vector_numbers.size() - 1];
                commands.deleteCommands(begin, end);
            }
            updateCommands();
            commands.setSelectedCommand(0);
        }
    }
}

void MainWindow::addLineCommand()
{
    if(ui->editorTab->isVisible())
    {
        if(ui->smlEditorTab->isVisible())
        {
            //LineDialog(this).exec();
        }
    }
    updateCommands();
}

void MainWindow::updateCoordinates()
{
    MachineTool &i = MachineTool::Instance();

    VectorDouble current = i.getCurrentCoordinates();
    VectorDouble base = i.getBaseCoordinates();
    VectorDouble park = i.getParkCoordinates();

    std::vector<std::pair<QListWidget*, VectorDouble>> widgets = {
        { ui->currentCoordinatesListWidget, current },
        { ui->baseCoordinatesListWidget, base },
        { ui->parkCoordinatesListWidget, park }
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

void MainWindow::updatePoints()
{
    std::vector<Point> points = PointsManager::Instance().getPoints();

    std::vector<QTableWidget*> tables = { ui->pointsTableWidget, ui->pointsTableWidget_2 };

    // проходим по каждой таблице
    for (auto table = tables.begin(); table != tables.end(); table++)
    {
        // очищаем текущую таблицу
        (*table)->setRowCount(0);

        // проходим по всем точкам
        for (unsigned int i = 0; i < points.size(); i++)
        {
            // координаты текущей точки
            //std::vector<double> pointCoordinates = { points[i].x, points[i].y, points[i].z, points[i].a, points[i].b };
            std::vector<double> pointCoordinates = points[i].getCoordinates();

            // добавляем строку в таблицу для текущей точки
            (*table)->insertRow(i);

            // отображаем координаты текущей точки
            for (unsigned int coordinate = 0; coordinate < pointCoordinates.size(); coordinate++)
                (*table)->setItem(i, coordinate, new QTableWidgetItem( QString::number(pointCoordinates[coordinate])) );
        }
    }
}

void MainWindow::updateCommands()
{
    auto commands = CommandInterpreter::Instance().getCommands();

    QTreeWidget*  editorField = ui->smlEditorTreeWidget;

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
        switch(commands[i]->getId())
        {
            /*case CMD_FOR:
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
            }*/
            default:
            {
                item = new QTreeWidgetItem(previousParent);
                break;
            }
        }



        item->setText(0, QString::number(i+1));
        QString commandColor = QString::fromStdString(commands[i]->getEditorColor());
        item->setTextColor(1, QColor(commandColor));
        item->setTextColor(2, QColor(commandColor));

        item->setText(1, commands[i]->getName());
        item->setText(2, commands[i]->getArguments());
        items.append(item);
    }
    editorField->insertTopLevelItems(0, items);
    editorField->expandAll();
    for(int i=0; i<2; i++)
    {
        editorField->resizeColumnToContents(i);
    }
}

void MainWindow::updateBatteryStatus()
{
    #ifdef Q_OS_WIN
        SYSTEM_POWER_STATUS status;
        GetSystemPowerStatus(&status);

        if ((status.BatteryLifePercent < 0) || (status.BatteryLifePercent > 100))
        status.BatteryLifePercent = 100;

        ui->batteryProgressBar->setValue(status.BatteryLifePercent);
    #endif
    #ifdef Q_OS_OSX
        ui->batteryProgressBar->setValue(100);
    #endif
}

void MainWindow::updateBaseStatus()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getBaseStatus())
    {
       ui->edgesControlCheckBox->setEnabled(true);
       ui->toolLengthSensorPushButton->setEnabled(true);
    }
    else
    {
        ui->edgesControlCheckBox->setEnabled(false);
        ui->toolLengthSensorPushButton->setEnabled(false);
    }
}

void MainWindow::updateKabriolAvaliability()
{
    if(ui->kabriolOffRadioButton->isChecked())
    {
        ui->movementBNegativePushButton->setEnabled(false);
        ui->movementBPositivePushButton->setEnabled(false);
    }
    if(ui->kabriolServoRadioButton->isChecked() || ui->kabriolOnRadioButton->isChecked())
    {
        ui->movementBNegativePushButton->setEnabled(true);
        ui->movementBPositivePushButton->setEnabled(true);
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
        ui->movementXPositivePushButton,
        ui->movementXNegativePushButton,
        ui->movementYPositivePushButton,
        ui->movementYNegativePushButton,

        ui->movementXPositiveYPositivePushButton,
        ui->movementXPositiveYNegativePushButton,
        ui->movementXNegativeYPositivePushButton,
        ui->movementXNegativeYNegativePushButton,

        ui->movementZPositivePushButton,
        ui->movementZNegativePushButton,

        ui->movementAPositivePushButton,
        ui->movementANegativePushButton,

        ui->movementBPositivePushButton,
        ui->movementBNegativePushButton
    };

    for (std::vector<QPushButton*>::iterator i = movementButtons.begin(); i != movementButtons.end(); i++)
        (*i)->setAutoRepeat(state);
}

void MainWindow::on_discreteRadioButton_1_clicked()
{
    MachineTool::Instance().setMovementStep(0.01);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    MachineTool::Instance().setMovementStep(0.1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    MachineTool::Instance().setMovementStep(1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    MachineTool::Instance().setMovementStep(10);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    MachineTool::Instance().setMovementStep(0);

    enableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(true);
}

void MainWindow::on_movementXPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
    v.x = 1;

    i.stepMove(v);
}

void MainWindow::on_movementXNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
    v.x = -1;

    i.stepMove(v);
}

void MainWindow::on_movementYPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movementYNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movementXNegativeYPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = -1;
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movementXPositiveYPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = 1;
    v.y = 1;

    i.stepMove(v);
}

void MainWindow::on_movementXNegativeYNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = -1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movementXPositiveYNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = 1;
    v.y = -1;

    i.stepMove(v);
}

void MainWindow::on_movementZPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.z = 1;

    i.stepMove(v);
}

void MainWindow::on_movementZNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.z = -1;

    i.stepMove(v);
}

void MainWindow::on_movementAPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.a = 1;

    i.stepMove(v);
}

void MainWindow::on_movementANegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.a = -1;

    i.stepMove(v);
}

void MainWindow::on_movementBPositivePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.b = 1;

    i.stepMove(v);
}

void MainWindow::on_movementBNegativePushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.b = -1;

    i.stepMove(v);
}

void MainWindow::on_feedrateScrollBar_valueChanged(int value)
{
    MachineTool::Instance().setVelocity(value);

    ui->feedrateLcdNumber->display(value);
}

void MainWindow::on_rotationsScrollBar_valueChanged(int value)
{
    MachineTool::Instance().setRotation(value);

    ui->rotationsLcdNumber->display(value);
}

void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

void MainWindow::on_pointsAmountPushButton_clicked()
{
    QMessageBox(QMessageBox::Information, "Количество точек", QString::number(ui->pointsTableWidget->rowCount())).exec();
}

void MainWindow::on_parkPushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v = i.getBaseCoordinates();
    i.setParkCoordinates(v);
}

void MainWindow::on_zeroPushButton_clicked()
{
    MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v = i.getBaseCoordinates();
    i.setNewZeroCoordinates(v);
}

void MainWindow::on_pointAddPushButton_clicked()
{
    AddPointDialog* addPoint = new AddPointDialog(this);
    addPoint->exec();
    delete addPoint;
    //Point tmp = Point(rand(), rand(), rand(), rand(), rand());
    //CommandInterpreter::Instance().addPoint(tmp);
    updatePoints();
}

void MainWindow::on_pointDeletePushButton_clicked()
{
    PointsManager& instance = PointsManager::Instance();
    QList<QTableWidgetItem*> selected = ui->pointsTableWidget->selectedItems();
    std::set<int> rows;

    for (QList<QTableWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++)
    {
        int row = ui->pointsTableWidget->row(*i);
        rows.insert(row);
    }

    for (std::set<int>::reverse_iterator i = rows.rbegin(); i != rows.rend(); i++)
    {
        instance.removePoint(*i);
    }

    updatePoints();
}

void MainWindow::on_pointCursorPushButton_clicked()
{
    MouseToSelectionPointDialog* toPoint = new MouseToSelectionPointDialog(this);
    toPoint->exec();
    delete toPoint;

    PointsManager& point_table = PointsManager::Instance();

    unsigned int point_to_select = point_table.getSelectedPoint();
    ui->pointsTableWidget->selectRow(point_to_select);
}

void MainWindow::on_pointEditPushButton_clicked()
{
    QItemSelectionModel *select = ui->pointsTableWidget->selectionModel();
    if(select->hasSelection())
    {
        //select->selectedRows();

        int current_row = select->currentIndex().row();

        PointsManager& point_table = PointsManager::Instance();
        point_table.setSelectedPoint(current_row);

        EditPointDialog* editPoint = new EditPointDialog(this);
        editPoint->exec();
        delete editPoint;
        updatePoints();
    }
    else
    {
         QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка не выбрана")).exec();
    }
}

void MainWindow::on_pointsTableWidget_doubleClicked(const QModelIndex &index)
{
    QItemSelectionModel *select = ui->pointsTableWidget->selectionModel();
    if(select->hasSelection())
    {
        int current_row = index.row();

        PointsManager& point_table = PointsManager::Instance();
        point_table.setSelectedPoint(current_row);

        EditPointDialog* editPoint = new EditPointDialog(this);
        editPoint->exec();
        delete editPoint;
        updatePoints();
    }
    else
    {
         QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка не выбрана")).exec();
    }
}

void MainWindow::on_pointCopyPushButton_clicked()
{
    PointsManager& instance = PointsManager::Instance();
    std::vector<Point> points = instance.getPoints();

    QList<QTableWidgetItem*> selected = ui->pointsTableWidget->selectedItems();
    std::set<int> rows;

    for (QList<QTableWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++)
    {
        int row = ui->pointsTableWidget->row(*i);
        rows.insert(row);
    }

    for (std::set<int>::iterator i = rows.begin(); i != rows.end(); i++)
    {
        instance.addPoint(points[*i]);
    }

    updatePoints();
}

void MainWindow::on_commandsToolsListWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    std::vector<Command*> commands = instance.getCommands();

    QTreeWidget* editorField = ui->smlEditorTreeWidget;

    QItemSelectionModel *select = editorField->selectionModel();
    if(!select->hasSelection())
    {
        unsigned int current_row = commands.size();
        instance.setSelectedCommand(current_row);
    }

    int row = index.row();

    QString name = ui->commandsToolsListWidget->item(row)->text();

    //COMMAND cmd = getCommandByName(name.toStdString());

    /*
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
            command.commandColor = COMMANDCOLORS[cycleColor];

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
            command.commandColor = COMMANDCOLORS[functionColor];

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

            command.commandColor = COMMANDCOLORS[zeroColor];

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

            command.commandColor = COMMANDCOLORS[finishColor];

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
    */
}

void MainWindow::on_smlEditorTreeWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& commandInterpreter = CommandInterpreter::Instance();
    commandInterpreter.setSelectedCommandEditSignal(true);
    QString name = ui->smlEditorTreeWidget->currentItem()->text(1);
    //COMMAND cmd = getCommandByName(name.toStdString());
    /*
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
    update_commands();*/
}

void MainWindow::on_smlEditorTreeWidget_clicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    unsigned int current_row;
    setSelectedCommandVectorNumber(current_row);
    instance.setSelectedCommand(current_row);
}

void MainWindow::setSelectedCommandVectorNumber(unsigned int& current_row)
{
    //получаем значение из нулевого столбца выделнного элемента
    QTreeWidget* editorField = ui->smlEditorTreeWidget;
    QList<QTreeWidgetItem *> selected_items = editorField->selectedItems();
    QTreeWidgetItem* item = selected_items[0];
    std::string s  = item->text(0).toStdString();
    current_row = std::stoi(s) - 1;
}

void MainWindow::updateEdgesControlStatus()
{
    MachineTool& instance = MachineTool::Instance();
    if(instance.getBaseStatus())
    {
        if(instance.getEdgesControlEnable())
        {
            ui->edgesControlCheckBox->setChecked(true);
            ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
            ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
            ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
        }
        else
        {
            ui->edgesControlCheckBox->setChecked(false);
            ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
            ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
            ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
        }
    }
    else
    {
        ui->edgesControlCheckBox->setEnabled(false);
        ui->edgesControlCheckBox->setChecked(false);
        ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
        ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
        ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
    }
}

void MainWindow::on_toBasePushButton_clicked()
{
    MachineTool& instance = MachineTool::Instance();
    instance.setBaseStatus(true);
    instance.setEdgesControlEnable(true);
    updateBaseStatus();
    updateEdgesControlStatus();
}

void MainWindow::on_edgesControlCheckBox_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getEdgesControlEnable())
    {
       instance.setEdgesControlEnable(false);
       ui->edgesControlCheckBox->setChecked(false);
       ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
       ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
       ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
    }
    else
    {
        instance.setEdgesControlEnable(true);
        ui->edgesControlCheckBox->setChecked(true);
        ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
        ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
        ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
    }
}

void MainWindow::on_spindelEnablePushButton_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(instance.getSpindleEnable())
    {
        //ui->spindle_enable_pushButton->setStyleSheet("");
        ui->spindelEnablePushButton->setStyleSheet("background-color: #2E8B57; color: #fff; border: 1px solid #000");
        ui->spindelEnablePushButton->setText("F1 - Включить шпиндель");
        instance.setSpindleEnable(false);
    }
    else
    {
        ui->spindelEnablePushButton->setStyleSheet("background-color: #B22222; color: #fff; border: 1px solid #000");
        ui->spindelEnablePushButton->setText("F1 - Выключить шпиндель");
        instance.setSpindleEnable(true);
    }
}

void MainWindow::on_millWarmingPushButton_clicked()
{
    MachineTool &instance = MachineTool::Instance();
    if(!instance.getSpindleWarmUp())
    {
        instance.setSpindleWarmUp(true);
        ui->spindelEnablePushButton->setEnabled(true);
        ui->spindelEnablePushButton->setStyleSheet("background-color: #2E8B57; color: #fff; border: 1px solid #000");
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
    ui->gcodesEditorTextEdit->setPlainText(content);
}

void MainWindow::parse7kamToSml(QString &tmp)
{
    CommandInterpreter &commands = CommandInterpreter::Instance();
    int limit = commands.getCommands().size() - 1;
    if(limit >= 0)
    {
        commands.deleteCommands(0, limit);
        updateCommands();
    }
    std::string commandsList = tmp.toStdString();
    while(commandsList.length() != 0)
    {
        parse7kamToSmlStep(commandsList);
    }
}

void MainWindow::parse7kamToSmlStep(std::string &tmp)
{
    /*
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
        newCommand.commandColor = COMMANDCOLORS[defaultColor];
        break;
    }
    case 1:
    {
        newCommand.id = CMD_TTARC;
        newCommand.commandColor = COMMANDCOLORS[defaultColor];
        break;
    }
    case 4:
    {
        newCommand.id = CMD_LINE;
        newCommand.commandColor = COMMANDCOLORS[defaultColor];
        break;
    }
    case 10:
    {
        newCommand.id = CMD_ZERO;
        newCommand.commandColor = COMMANDCOLORS[zeroColor];
        break;
    }
    case 14:
    {
        newCommand.id = CMD_SPEED;
        newCommand.commandColor = COMMANDCOLORS[warningColor];
        break;
    }
    case 19:
    {
        newCommand.id = CMD_LABEL;
        newCommand.commandColor = COMMANDCOLORS[labelColor];
        break;
    }
    case 20:
    {
        newCommand.id = CMD_CALL;
        newCommand.commandColor = COMMANDCOLORS[functionColor];
        break;
    }
    case 21:
    {
        newCommand.id = CMD_RETURN;
        newCommand.commandColor = COMMANDCOLORS[functionColor];
        break;
    }
    case 22:
    {
        newCommand.id = CMD_GOTO;
        newCommand.commandColor = COMMANDCOLORS[labelColor];
        break;
    }
    case 23:
    {
        newCommand.id = CMD_FOR;
        newCommand.commandColor = COMMANDCOLORS[cycleColor];
        break;
    }
    case 24:
    {
        newCommand.id = CMD_ENDFOR;
        newCommand.commandColor = COMMANDCOLORS[cycleColor];
        break;
    }
    case 25:
    {
        newCommand.id = CMD_STOP;
        newCommand.commandColor = COMMANDCOLORS[warningColor];
        break;
    }
    case 26:
    {
        newCommand.id = CMD_END;
        newCommand.commandColor = COMMANDCOLORS[finishColor];
        break;
    }
    case 27:
    {
        newCommand.id = CMD_COMMENT;
        newCommand.commandColor = COMMANDCOLORS[commentColor];
        break;
    }
    case 28:
    {
        newCommand.id = CMD_PAUSE;
        newCommand.commandColor = COMMANDCOLORS[warningColor];
        break;
    }
    case 31:
    {
        newCommand.id = CMD_PROC;
        newCommand.commandColor = COMMANDCOLORS[functionColor];
        break;
    }
    default:
        newCommand.id = CMD_UNDEFINED;
        position = tmp.length();
        break;
    }

    // получаем аргументы команды
    std::string commandArguments;
    bool space = false;
    for(auto i : tmp)
    {
        position++;
        // откидываем id
        if(i == ' ' && !space)
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
    */
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
                ui->xDimensionLineEdit,
                ui->yDimensionLineEdit,
                ui->zDimensionLineEdit,
                ui->aDimensionLineEdit,
                ui->bDimensionLineEdit,

                ui->xAxisJerkLineEdit,
                ui->xAxisAccelerationLineEdit,
                ui->xAxisVelocityLineEdit,
                ui->xAxisChannelLineEdit,
                ui->xAxisBasingVelocityLineEdit,

                ui->yAxisJerkLineEdit,
                ui->yAxisAccelerationLineEdit,
                ui->yAxisVelocityLineEdit,
                ui->yAxisChannelLineEdit,
                ui->yAxisBasingVelocityLineEdit,

                ui->zAxisJerkLineEdit,
                ui->zAxisAccelerationLineEdit,
                ui->zAxisVelocityLineEdit,
                ui->zAxisChannelLineEdit,
                ui->zAxisBasingVelocityLineEdit,

                ui->aAxisJerkLineEdit,
                ui->aAxisAccelerationLineEdit,
                ui->aAxisVelocityLineEdit,
                ui->aAxisChannelLineEdit,
                ui->aAxisBasingVelocityLineEdit,

                ui->bAxisJerkLineEdit,
                ui->bAxisAccelerationLineEdit,
                ui->bAxisVelocityLineEdit,
                ui->bAxisChannelLineEdit,
                ui->bAxisBasingVelocityLineEdit,

                ui->criticalAngleLineEdit,
                ui->bufferSizeLineEdit,
                ui->collinearityToleranceLineEdit,
                ui->maximumDevationLineEdit,
                ui->smoothingAngleLineEdit,

                ui->zeroLevelSensorLineEdit,
                ui->toolLengthSensorLineEdit,
                ui->velocityFromSensorLineEdit,
                ui->minimumSearchingVelocityLineEdit
            };
            return mechanicalSettingsVector;
            break;
        }
        case 2:
        {
            std::vector<QLineEdit*> electricalSettingsFieldVector =
            {
                ui->xAxisStepLineEdit,
                ui->yAxisStepLineEdit,
                ui->zAxisStepLineEdit,
                ui->aAxisStepLineEdit,
                ui->bAxisStepLineEdit
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
                ui->xAxisInvertCheckBox,
                ui->yAxisInvertCheckBox,
                ui->zAxisInvertCheckBox,
                ui->aAxisInvertCheckBox,
                ui->bAxisInvertCheckBox
            };
            return invertAxisVector;
            break;
        }
        case 2:
        {
            std::vector<QCheckBox*> externalDevicesVector =
            {
                ui->millCheckBox,
                ui->kabriolCheckBox,
                ui->lubricationSystemCheckBox,
                ui->toolChangeCheckBox,
                ui->laserCheckBox,
                ui->wacuumTableCheckBox,
                ui->toolLengthSensorCheckBox
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

void MainWindow::on_changeMechanicalSettingsPushButton_clicked()
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

void MainWindow::on_cancelMechanicalSettingsPushButton_clicked()
{
    dimensionsFromMachineTool();
    directionsFromMachineTool();
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

void MainWindow::on_applyMechanicalSettingsPushButton_clicked()
{

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

void MainWindow::on_changeElecricalSettingsPushButton_clicked()
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
//    VectorDouble v =
//    {
//        ui->x_axis_step_lineEdit->text().toDouble(),
//        ui->y_axis_step_lineEdit->text().toDouble(),
//        ui->z_axis_step_lineEdit->text().toDouble(),
//        ui->a_axis_step_lineEdit->text().toDouble(),
//        ui->b_axis_step_lineEdit->text().toDouble(),
//    };
//    instance.setDistanceByOneStep(v);

//    v.x = ui->x_axis_mm_lineEdit->text().toDouble();
//    v.y = ui->y_axis_mm_lineEdit->text().toDouble();
//    v.z = ui->z_axis_mm_lineEdit->text().toDouble();
//    v.a = ui->a_axis_mm_lineEdit->text().toDouble();
//    v.b = ui->b_axis_mm_lineEdit->text().toDouble();
//    instance.setStepQuantityByOneMm(v);

    std::map<std::string, bool> m =
    {
        {"mill", ui->millCheckBox->isChecked()},
        {"kabriol", ui->kabriolCheckBox->isChecked()},
        {"lubrication_system", ui->lubricationSystemCheckBox->isChecked()},
        {"tool_change", ui->toolChangeCheckBox->isChecked()},
        {"laser", ui->laserCheckBox->isChecked()},
        {"wacuum_table", ui->wacuumTableCheckBox->isChecked()},
        {"tool_length_sensor", ui->toolLengthSensorCheckBox->isChecked()}
    };
    instance.setExternalDevices(m);
}

void MainWindow::on_applyElectricalSettingsPushButton_clicked()
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

void MainWindow::electricialSettingsFromMachineTool()
{
    MachineTool &instance = MachineTool::Instance();
//    VectorDouble v = instance.getDistanceByOneStep();
//    ui->x_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
//    ui->y_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
//    ui->z_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
//    ui->a_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
//    ui->b_axis_step_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));

//    v = instance.getStepQuantityByOneMm();
//    ui->x_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
//    ui->y_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
//    ui->z_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
//    ui->a_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
//    ui->b_axis_mm_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));

    std::map<std::string, bool> m = instance.getExternalDevices();
    if(m["mill"])
    {
        ui->millCheckBox->setChecked(true);
    }
    else
    {
        ui->millCheckBox->setChecked(false);
    }

    if(m["kabriol"])
    {
        ui->kabriolCheckBox->setChecked(true);
    }
    else
    {
        ui->kabriolCheckBox->setChecked(false);
    }

    if(m["lubrication_system"])
    {
        ui->lubricationSystemCheckBox->setChecked(true);
    }
    else
    {
        ui->lubricationSystemCheckBox->setChecked(false);
    }

    if(m["tool_change"])
    {
        ui->toolChangeCheckBox->setChecked(true);
    }
    else
    {
        ui->toolChangeCheckBox->setChecked(false);
    }

    if(m["laser"])
    {
        ui->laserCheckBox->setChecked(true);
    }
    else
    {
        ui->laserCheckBox->setChecked(false);
    }

    if(m["wacuum_table"])
    {
        ui->wacuumTableCheckBox->setChecked(true);
    }
    else
    {
        ui->wacuumTableCheckBox->setChecked(false);
    }
    if(m["tool_length_sensor"])
    {
        ui->toolLengthSensorCheckBox->setChecked(true);
    }
    else
    {
        ui->toolLengthSensorCheckBox->setChecked(false);
    }
}

void MainWindow::on_cancelElectricalSettingsPushButton_clicked()
{
    electricialSettingsFromMachineTool();

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

void MainWindow::dimensionsFromMachineTool()
{
    MachineTool &instance = MachineTool::Instance();
//    VectorDouble v = instance.getDimensions();
//    ui->x_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
//    ui->y_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
//    ui->z_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
//    ui->a_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
//    ui->b_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));
}

void MainWindow::directionsFromMachineTool()
{
    MachineTool &instance = MachineTool::Instance();
//    std::vector<bool> v = instance.getDirections();

//    std::vector<QCheckBox*> mechanicalCheckBoxes = makeQCheckBoxVector(1);
//    for(auto i : mechanicalCheckBoxes)
//    {
//        i->setChecked(false);
//    }

    /*if(v.x == 1)
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
    }*/
}

void MainWindow::kinematicsSettingsFromMachineTool()
{
//    MachineTool &instance = MachineTool::Instance();
//    std::vector<AxisKFlopSettings> tmp = instance.getAxisKFlopSettings();
}

void MainWindow::on_gcodesEditorTextEdit_textChanged()
{
    QString text = ui->gcodesEditorTextEdit->toPlainText();
}

void MainWindow::on_userToolsListWidget_doubleClicked(const QModelIndex &index)
{
    CommandInterpreter& instance = CommandInterpreter::Instance();
    std::vector<Command*> commands = instance.getCommands();

    QTreeWidget* editorField = ui->smlEditorTreeWidget;

    QItemSelectionModel *select = editorField->selectionModel();
    if(!select->hasSelection())
    {
        unsigned int current_row = commands.size();
        instance.setSelectedCommand(current_row);
    }

    int row = index.row();

    QString name = ui->userToolsListWidget->item(row)->text();

    if(name == "Добавить устройство")
    {
        AddDeviceDialog(this).exec();
    }
    updateCommands();
}

void MainWindow::on_importsettings_action_triggered()
{
    SettingsManager settingsManager;
    settingsManager.importSettings();
}

void MainWindow::on_savesettings_action_triggered()
{
    SettingsManager settingsManager;
    settingsManager.exportSettings();
}

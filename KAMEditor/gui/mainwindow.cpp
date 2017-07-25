#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // окно на весь экран
    QMainWindow::showMaximized();



    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    // установка древесной структуры в 1 столбец виджета отображения sml-команд
    QTreeWidget*  editorField = ui->smlEditorTreeWidget;
    editorField->setTreePosition(1);

    // устанвиливаем подсветку текста в виджете отображения G-кодов
    hightlighter = new GCodesSyntaxHighlighter(this);
    hightlighter->setDocument(ui->gcodesEditorTextEdit->document());
    hightlighter->setPattern();


    // перевод кнопок, требующих дополнительных действий перед активацией, в неактивное состояние
    ui->spindelEnablePushButton->setEnabled(false);
    ui->spindelEnablePushButton->setStyleSheet("margin: 1px");
    ui->toolLengthSensorPushButton->setEnabled(false);

    // инициализация станка
    initializeMachineTool();

    // задаем горячие клавиши перемещения
    setupShortcuts();

    // синхронизаци контроля габаритов и соответствующих элементов интерфейса
    updateEdgesControlStatus();
    connect(ui->edgesControlCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateEdgesControlStatus()));

    // connects
    //connect(ui->pointEditPushButton, SIGNAL(clicked(bool)), this, SLOT(on_pointsTableWidget_doubleClicked(QModelIndex)));
    connect(ui->pointsTableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_pointEditPushButton_clicked()));
    connect(ui->pointsTableWidget_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_pointEditPushButton_clicked()));

    initializeTimer();
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

#ifdef Q_OS_WIN
    delete u1Manager;
#endif
    delete machineTool;

    delete hightlighter;
    //delete u1Connector;
}

void MainWindow::initializeMachineTool()
{
    machineTool = new MachineTool(VENDOR_ID, PRODUCT_ID, "semir", 5);
    updateSettingsFields();
    initializeCoordinatesFields();
    initializePointsManager();

#ifdef Q_OS_WIN
    try
    {
        u1Manager = new UsbXpressDeviceManager(machineTool);
        showMachineToolConnected();
    }
    catch(std::runtime_error e)
    {
        u1Manager = nullptr;
        QMessageBox(QMessageBox::Warning, "Ошибка подключения", e.what()).exec();
        showMachineToolDisconnected();
    }
#endif
    /*u1Connector = new UsbDevicesManager(machineTool);
    if(u1Connector->getU1() != NULL)
    {
        ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
        ui->statusBar->showMessage("Machine Tool is connected");
    }
    else
    {
        ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
        ui->statusBar->showMessage("Machine Tool is disconected");
    }*/
}

void MainWindow::updateSettingsFields()
{
    updateAxisSettingsField();
    updateSensorsSettingsField();
}

void MainWindow::updateAxisSettingsField()
{
    ui->axisSettingsTableWidget->clear();

    std::vector< std::shared_ptr<Axis> > axises = machineTool->getMovementController().getAxises();
    int axisCount = axises.size();

    QStringList qHorizontalHeaders;
    for(auto axis : axises)
    {
        QString header = QString("Ось " + QString::fromStdString(axis->getName()));
        qHorizontalHeaders.append(header);
    }

    ui->axisSettingsTableWidget->setColumnCount(axisCount);
    ui->axisSettingsTableWidget->setHorizontalHeaderLabels(qHorizontalHeaders);

    QStringList qVerticalHeaders =
    {
        "Длина",
        "Шаг",
        "Направление",
        "Рывок",
        "Ускорение",
        "Скорость",
        "Скорость Базирования",
        "Канал"
    };
    ui->axisSettingsTableWidget->setRowCount(qVerticalHeaders.size());
    ui->axisSettingsTableWidget->setVerticalHeaderLabels(qVerticalHeaders);


    for(int i = 0; i < ui->axisSettingsTableWidget->horizontalHeader()->count(); i++)
    {
        ui->axisSettingsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->axisSettingsTableWidget->verticalHeader()->count(); j++)
        {
            QTableWidgetItem *item = fillAxisesSettingsTable(axises, i, j);
            ui->axisSettingsTableWidget->setItem(j, i, item);
        }
    }
}

QTableWidgetItem* MainWindow::fillAxisesSettingsTable(const std::vector< std::shared_ptr<Axis> > &axises, int axisIndex, int parametrIndex)
{
    std::string text = "Здесь должны быть параметры оси";
    switch (parametrIndex) {
    case 0:
        text = std::to_string(axises[axisIndex]->getLength());
        break;
    case 1:
        text = std::to_string(axises[axisIndex]->getStep());
        break;
    case 2:
        text = std::to_string(axises[axisIndex]->getInvertDirection());
        break;
    case 3:
        text = std::to_string(axises[axisIndex]->getJerk());
        break;
    case 4:
        text = std::to_string(axises[axisIndex]->getAcceleration());
        break;
    case 5:
        text = std::to_string(axises[axisIndex]->getVelocity());
        break;
    case 6:
        text = std::to_string(axises[axisIndex]->getBasingVelocity());
        break;
    case 7:
        text = std::to_string(axises[axisIndex]->getChannel());
        break;
    default:
        text = "Unknown parametr";
        break;
    }
    return new QTableWidgetItem(QString::fromStdString(text));
}


void MainWindow::updateSensorsSettingsField()
{
    std::vector< std::shared_ptr<Sensor> > sensors = machineTool->getSensorsManager().getSensors();
    int sensorsCount = sensors.size();
    QStringList sensorsLabels;
    for(auto sensor : sensors)
    {
        sensorsLabels.push_back(QString::fromStdString(sensor->getName()));
    }
    ui->sensorsTableWidget->setRowCount(sensorsCount);
    ui->sensorsTableWidget->setVerticalHeaderLabels(sensorsLabels);

    QStringList qHorizontalHeaders =
    {
        "Номер порта",
        "Номер выхода",
        "Состояние по умолчанию",
    };
    ui->sensorsTableWidget->setColumnCount(qHorizontalHeaders.size());
    ui->sensorsTableWidget->setHorizontalHeaderLabels(qHorizontalHeaders);

    // растянуть таблицу с координатами редактора точек
    for (int i = 0; i < ui->sensorsTableWidget->horizontalHeader()->count(); i++)
    {
        ui->sensorsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->sensorsTableWidget->verticalHeader()->count(); j++)
        {
            QTableWidgetItem *item = fillSensorsSettingsTable(sensors, i, j);
            ui->sensorsTableWidget->setItem(j, i, item);
        }
    }
}

QTableWidgetItem* MainWindow::fillSensorsSettingsTable(const std::vector< std::shared_ptr<Sensor> > &sensors, int parametrIndex, int sensorIndex)
{
    std::string text = "Здесь должны быть параметры Датчика";
    switch (parametrIndex) {
    case 0:
        text = std::to_string(sensors[sensorIndex]->getPortNumber());
        break;
    case 1:
        text = std::to_string(sensors[sensorIndex]->getInputNumber());
        break;
    case 2:
        text = std::to_string(sensors[sensorIndex]->getIsEnable());
        break;
    default:
        text = "Unknown parametr";
        break;
    }
    return new QTableWidgetItem(QString::fromStdString(text));
}


void MainWindow::initializeCoordinatesFields()
{
    QStringList axisesLabels;
    std::vector< std::shared_ptr<Axis> > axises = machineTool->getMovementController().getAxises();
    for(auto axis : axises)
    {
        axisesLabels.push_back(QString(QString::fromStdString(axis->getName()) + ": "));
    }
    ui->currentCoordinatesListWidget->clear();
    ui->currentCoordinatesListWidget->addItems(axisesLabels);

    ui->baseCoordinatesListWidget->clear();
    ui->baseCoordinatesListWidget->addItems(axisesLabels);

    ui->parkCoordinatesListWidget->clear();
    ui->parkCoordinatesListWidget->addItems(axisesLabels);
}

void MainWindow::initializePointsManager()
{
    std::vector< std::shared_ptr<Axis> > axises = machineTool->getMovementController().getAxises();
    int axisesCount = axises.size();
    QStringList axisesLabels;

    for(auto axis : axises)
    {
        axisesLabels.push_back(QString::fromStdString(axis->getName()));
    }

    ui->pointsTableWidget->setColumnCount(axisesCount);
    ui->pointsTableWidget_2->setColumnCount(axisesCount);

    ui->pointsTableWidget->setHorizontalHeaderLabels(axisesLabels);
    ui->pointsTableWidget_2->setHorizontalHeaderLabels(axisesLabels);

    // растянуть таблицу с координатами редактора точек
    for (int i = 0; i < ui->pointsTableWidget->horizontalHeader()->count(); i++)
    {
        ui->pointsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->pointsTableWidget_2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // в таблице редактора точек выделяется целиком вся строка
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointsTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::initializeTimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(100);
    timer->start();
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
        std::make_tuple("Down", ui->movementZNegativePushButton, SLOT(on_movementZNegativePushButton_clicked())),
        std::make_tuple("Up", ui->movementZPositivePushButton, SLOT(on_movementZPositivePushButton_clicked())),
        std::make_tuple("Left", ui->movementANegativePushButton, SLOT(on_movementANegativePushButton_clicked())),
        std::make_tuple("Right", ui->movementAPositivePushButton, SLOT(on_movementAPositivePushButton_clicked())),
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
    updateBatteryStatus();
#ifdef Q_OS_WIN
    if(u1Manager != nullptr)
    {
        updateMachineToolStatus();
        updateCoordinates();
        //updateKabriolAvaliability();
        //updateBaseStatus();
    }
#endif
}

void MainWindow::deleteSelectedCommands()
{
}

void MainWindow::updateCoordinates()
{
    /*MachineTool &i = MachineTool::Instance();

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
    }*/
}

void MainWindow::updatePoints()
{
    PointsManager pointsManager = machineTool->getPointsManager();
    unsigned int pointsCount = pointsManager.pointCount();
    std::vector<QTableWidget*> tables = { ui->pointsTableWidget, ui->pointsTableWidget_2 };
    // проходим по каждой таблице
    for (auto table = tables.begin(); table != tables.end(); table++)
    {
        // очищаем текущую таблицу
        (*table)->setRowCount(0);

        // проходим по всем точкам
        for (unsigned int i = 0; i < pointsCount; i++)
        {
            std::shared_ptr<Point> p = pointsManager[i];
            // добавляем строку в таблицу для текущей точки
            (*table)->insertRow(i);

            // отображаем координаты текущей точки
            for (unsigned int coordinate = 0; coordinate < p->size(); coordinate++)
            {
                std::string argument;
                try
                {
                    argument = std::to_string(p.get()->operator [](coordinate));
                }
                catch(std::out_of_range e)
                {
                    QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
                    break;
                }
                (*table)->setItem(i, coordinate, new QTableWidgetItem( QString::fromStdString(argument) ));
            }
        }
    }
}

void MainWindow::updateCommands()
{
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

void MainWindow::updateMachineToolStatus()
{
#ifdef Q_OS_WIN
    ui->recievedDataTextEdit->clear();
    try
    {
        byte_array recieved = u1Manager->getU1()->receiveData(16);
        QString recievedData;
        for(auto it : recieved)
        {
            recievedData = QString::number(it, 2);
            ui->recievedDataTextEdit->append(recievedData);
        }
        showMachineToolConnected();
    }
    catch(std::runtime_error e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
        timer->stop();
        showMachineToolDisconnected();
    }
#endif
}

void MainWindow::showMachineToolConnected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->showMessage("Machine Tool is connected");
}

void MainWindow::showMachineToolDisconnected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
    ui->statusBar->showMessage("Machine Tool is disconected");
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
    //MachineTool::Instance().setMovementStep(0.01);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    //MachineTool::Instance().setMovementStep(0.1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    //MachineTool::Instance().setMovementStep(1);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    //MachineTool::Instance().setMovementStep(10);

    disableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(false);
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    //MachineTool::Instance().setMovementStep(0);

    enableMovementButtonsShortcuts();
    setMovementButtonsRepeatState(true);
}

void MainWindow::on_movementXPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
    v.x = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
    v.x = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementYPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementYNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativeYPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = -1;
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXPositiveYPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = 1;
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativeYNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = -1;
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXPositiveYNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.x = 1;
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementZPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.z = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementZNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.z = -1;

    i.stepMove(v);*/

}

void MainWindow::on_movementAPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.a = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementANegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.a = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementBPositivePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.b = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementBNegativePushButton_clicked()
{
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.b = -1;

    i.stepMove(v);*/
}

void MainWindow::on_feedrateScrollBar_valueChanged(int value)
{
    //MachineTool::Instance().setVelocity(value);

    ui->feedrateLcdNumber->display(value);
}

void MainWindow::on_rotationsScrollBar_valueChanged(int value)
{
    //MachineTool::Instance().setRotation(value);

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

}

void MainWindow::on_zeroPushButton_clicked()
{

}

void MainWindow::on_pointAddPushButton_clicked()
{
    AddPointDialog* addPoint = new AddPointDialog(machineTool, this);
    addPoint->exec();
    updatePoints();
}

void MainWindow::on_pointDeletePushButton_clicked()
{
    QList<QTableWidgetItem*> selected = ui->pointsTableWidget->selectedItems();
    std::set<int> rows;

    for (QList<QTableWidgetItem*>::iterator i = selected.begin(); i != selected.end(); i++)
    {
        int row = ui->pointsTableWidget->row(*i);
        rows.insert(row);
    }

    for (std::set<int>::reverse_iterator i = rows.rbegin(); i != rows.rend(); i++)
    {
        std::shared_ptr<Point> p = machineTool->getPointsManager().operator [](*i);
        machineTool->getPointsManager().deletePoint(p);
    }
    updatePoints();
}

void MainWindow::on_pointCursorPushButton_clicked()
{
    /*MouseToSelectionPointDialog* toPoint = new MouseToSelectionPointDialog(this);
    toPoint->exec();
    delete toPoint;

    PointsManager& point_table = PointsManager::Instance();

    unsigned int point_to_select = point_table.getSelectedPoint();
    ui->pointsTableWidget->selectRow(point_to_select);*/
}

void MainWindow::on_pointEditPushButton_clicked()
{
    QItemSelectionModel *select;
    if(ui->smlEditorTab->isVisible())
    {
        select = ui->pointsTableWidget_2->selectionModel();
    }
    else
    {
        select = ui->pointsTableWidget->selectionModel();
    }
    if(select->hasSelection())
    {
        //select->selectedRows();

        int current_row = select->currentIndex().row();
        AddPointDialog* editPoint = new AddPointDialog(machineTool, machineTool->getPointsManager().operator [](current_row), current_row, this);
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
    /*PointsManager& instance = PointsManager::Instance();
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

    updatePoints();*/
}

void MainWindow::updateEdgesControlStatus()
{
    if(ui->edgesControlCheckBox->isChecked())
    {
        ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
        ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
        ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #2E8B57");
    }
    else
    {
        ui->currentCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
        ui->baseCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
        ui->parkCoordinatesListWidget->setStyleSheet("border: 2px solid #B22222");
    }
}

void MainWindow::on_toBasePushButton_clicked()
{

}

void MainWindow::on_spindelEnablePushButton_clicked()
{
    /*
    ui->spindelEnablePushButton->setStyleSheet("background-color: #2E8B57; color: #fff; border: 1px solid #000");
    ui->spindelEnablePushButton->setText("F1 - Включить шпиндель");

    ui->spindelEnablePushButton->setStyleSheet("background-color: #B22222; color: #fff; border: 1px solid #000");
    ui->spindelEnablePushButton->setText("F1 - Выключить шпиндель");
    */
}

void MainWindow::on_millWarmingPushButton_clicked()
{

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

    ui->gcodesEditorTextEdit->setPlainText(content);
}


void MainWindow::on_gcodesEditorTextEdit_textChanged()
{
    QString text = ui->gcodesEditorTextEdit->toPlainText();
}

void MainWindow::on_importsettings_action_triggered()
{

}

void MainWindow::on_savesettings_action_triggered()
{

}

void MainWindow::on_startDegbugCommandLinkButton_clicked()
{
    ui->finishDebugCommandLinkButton->setEnabled(true);
    ui->startDegbugCommandLinkButton->setEnabled(false);
}

void MainWindow::on_finishDebugCommandLinkButton_clicked()
{
    ui->startDegbugCommandLinkButton->setEnabled(true);
    ui->finishDebugCommandLinkButton->setEnabled(false);
}

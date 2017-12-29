#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // окно на весь экран
    QMainWindow::showMaximized();

    setupMainWindowController();

    // настройка виджетов
    setupWidgets();

    emit ready();
}

MainWindow::~MainWindow()
{
    // удаляем горячие клавиши
    while (axisesShortcuts.size() > 0)
    {
        delete axisesShortcuts.back();
        axisesShortcuts.pop_back();
    }

    delete hightlighter;
    delete mainWindowController;
    delete ui;
}

void MainWindow::setupMainWindowController()
{
    mainWindowController = new MainWindowController();
    connect(this, SIGNAL(ready()), mainWindowController, SLOT(loadMachineToolSettings()));
}

void MainWindow::setupSettingsWidgets()
{
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateAxisesBoard()));
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateDevicesBoard()));
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateSensorsBoard()));
}

void MainWindow::setupWidgets()
{
    // задаем горячие клавиши
    setupAxisesShortcuts();
    // проводим настройку необходимых виджетов
    setupStatusBar();
    setupDisplays();
    setupCommandsEditorField();
    setupGCodesSyntaxHighlighter();
    setupEdgesControl();
    setupPointsEditorWidgets();
    setupEditorFileActionsPushButtons();
    setupCoordinatesDisplay();
    setupDevicesPanel();
    setupVelocityPanel();
    setupSpindelRotationsPanel();
    setupOptionsPanel();

    setupSettingsWidgets();
}

void MainWindow::setupCommandsEditorField()
{
    SMLEditorTreeWidget*  editorField = ui->smlEditorTreeWidget;
    // установка древесной структуры в 1 столбец виджета отображения sml-команд
    editorField->setTreePosition(1);

    // устанавливаем слоты, обрабатывающие сигналы дерева
    //connect(editorField, SIGNAL(copySignal()), this, SLOT(commandsCopySlot()));
    //connect(editorField, SIGNAL(cutSignal()), this, SLOT(commandsCutSlot()));
    //connect(editorField, SIGNAL(pasteSignal()), this, SLOT(commandsPasteSlot()));
    //connect(editorField, SIGNAL(undoSignal()), this, SLOT(commandsUndoSlot()));
    connect(mainWindowController, SIGNAL(commandsUpdated()), this, SLOT(updateCommandsEditorWidgets()));
    connect(editorField, SIGNAL(eraseSignal(QModelIndexList)), this, SLOT(deleteSelectedCommands(QModelIndexList)));
}

void MainWindow::setupStatusBar()
{
    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    // Подключение слотов для обработки сигналов контроллеров
    connect(mainWindowController, SIGNAL(kflopIsConnected()), this, SLOT(showMachineToolConnected()));
    connect(mainWindowController, SIGNAL(kflopIsDisconnected()), this, SLOT(showMachineToolDisconnected()));
    connect(mainWindowController, SIGNAL(u1IsDisconnected()), this, SLOT(showMachineToolDisconnected()));
    connect(mainWindowController, SIGNAL(machineToolStateIsChanged()), SLOT(showMachineToolConnected()));
}

void MainWindow::setupDisplays()
{
    connect(mainWindowController, SIGNAL(machineToolStateIsChanged()), this, SLOT(updateDisplays()));
    connect(mainWindowController, SIGNAL(u1IsDisconnected()), this, SLOT(updateDisplays()));
}

void MainWindow::setupGCodesSyntaxHighlighter()
{
    // устанвиливаем подсветку текста в виджете отображения G-кодов
    hightlighter = new GCodesSyntaxHighlighter(this);
    hightlighter->setDocument(ui->gcodesEditorTextEdit->document());
    hightlighter->setPattern();
}

void MainWindow::setupDevicesPanel()
{
    connect(mainWindowController, SIGNAL(u1IsConnected()), this, SLOT(updateDevicesPanel()));
    connect(mainWindowController, SIGNAL(u1IsDisconnected()), this, SLOT(updateDevicesPanel()));
}

void MainWindow::setupEdgesControl()
{
    // синхронизаци контроля габаритов и соответствующих элементов интерфейса
    updateEdgesControlStatus();
    connect(ui->edgesControlCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateEdgesControlStatus()));
}

void MainWindow::setupPointsEditorFields()
{
    // в таблице редактора точек выделяется целиком вся строка
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointsTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updatePointsEditorFields()));

    QList<SMLPointsTableWidget*> pointsEditorTableWidgets = {ui->pointsTableWidget, ui->pointsTableWidget_2};

    for(auto pointsEditorTableWidget : pointsEditorTableWidgets)
    {
        connect(pointsEditorTableWidget, SIGNAL(editSignal(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
        connect(pointsEditorTableWidget, SIGNAL(eraseSignal(QModelIndexList)), this, SLOT(deletePoints(QModelIndexList)));
        connect(pointsEditorTableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
    }
}

void MainWindow::setupPointsPushButtons()
{
    connect(ui->pointAddPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointAddPushButton_clicked()));
    connect(ui->pointDeletePushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointDeletePushButton_clicked()));
    connect(ui->pointCursorPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCursorPushButton_clicked()));
    connect(ui->pointCopyPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCopyPushButton_clicked()));

    updatePointsEditorButtons();
}

void MainWindow::setupVelocityPanel()
{
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateVelocityPanel()));
}

void MainWindow::setupSpindelRotationsPanel()
{
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateSpindelRotationsPanel()));
}

void MainWindow::setupOptionsPanel()
{
    connect(mainWindowController, SIGNAL(machineToolSettingsIsLoaded()), this, SLOT(updateOptionsPanel()));
}

void MainWindow::updateSettingsBoards()
{
    updateAxisesBoard();
    updateSensorsBoard();
    updateDevicesBoard();
}

void MainWindow::updateAxisesBoard()
{
    QStringList names = mainWindowController->getAxisesNames();
    QStringList axisesParametrsNames = mainWindowController->getAxisesParametrsNames();
    QList<QStringList> axisesSettings = mainWindowController->getAxisesSettings();

    ui->axisSettingsTableWidget->clear();
    ui->axisSettingsTableWidget->setColumnCount(names.size());
    ui->axisSettingsTableWidget->setHorizontalHeaderLabels(names);
    ui->axisSettingsTableWidget->setRowCount(axisesParametrsNames.size());
    ui->axisSettingsTableWidget->setVerticalHeaderLabels(axisesParametrsNames);

    for(int i = 0; i < ui->axisSettingsTableWidget->columnCount(); i++)
    {
        ui->axisSettingsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for(int i = 0; i < ui->axisSettingsTableWidget->rowCount(); i++)
    {
        ui->axisSettingsTableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for(int i = 0; i < ui->axisSettingsTableWidget->columnCount(); i++)
    {
        ui->axisSettingsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for(int j = 0; j < ui->axisSettingsTableWidget->rowCount(); j++)
        {
            ui->axisSettingsTableWidget->setItem(j, i, new QTableWidgetItem(axisesSettings[i][j]));
        }
    }
}

void MainWindow::updatePointsEditorWidgets()
{
<<<<<<< HEAD
    SettingsManager settings;
    settings.setupToMachineTool();
    dimensionsFromMachineTool();
    electricialSettingsFromMachineTool();
=======
    updatePointsEditorFields();
    updatePointsEditorButtons();
>>>>>>> mvc
}

void MainWindow::updateSensorsBoard()
{
    QStringList sensorsNames = mainWindowController->getSensorsNames();
    QStringList sensorsParametrsNames = mainWindowController->getSensorsParametrsNames();
    QList<QStringList> sensorsSettings = mainWindowController->getSensorsSettings();

    ui->sensorsSettingsTableWidget->clear();
    ui->sensorsSettingsTableWidget->setRowCount(sensorsNames.size());
    ui->sensorsSettingsTableWidget->setVerticalHeaderLabels(sensorsNames);
    ui->sensorsSettingsTableWidget->setColumnCount(sensorsParametrsNames.size());
    ui->sensorsSettingsTableWidget->setHorizontalHeaderLabels(sensorsParametrsNames);

    for(int i = 0; i < ui->sensorsSettingsTableWidget->columnCount(); i++)
    {
        ui->sensorsSettingsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < ui->sensorsSettingsTableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->sensorsSettingsTableWidget->columnCount(); j++)
        {
            ui->sensorsSettingsTableWidget->setItem(i, j, new QTableWidgetItem(sensorsSettings[i][j]));
        }
    }
}

void MainWindow::updateDevicesBoard()
{
    QStringList devicesNames = mainWindowController->getDevicesNames();
    QStringList devicesParametrsNames = mainWindowController->getDevicesParametrsNames();
    QList<QStringList> devicesSettings = mainWindowController->getDevicesSettings();

    ui->devicesSettingsTableWidget->clear();
    ui->devicesSettingsTableWidget->setRowCount(devicesNames.size());
    ui->devicesSettingsTableWidget->setVerticalHeaderLabels(devicesNames);
    ui->devicesSettingsTableWidget->setColumnCount(devicesParametrsNames.size());
    ui->devicesSettingsTableWidget->setHorizontalHeaderLabels(devicesParametrsNames);

    for(int i = 0; i < ui->devicesSettingsTableWidget->columnCount(); i++)
    {
        ui->devicesSettingsTableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    for (int i = 0; i < ui->devicesSettingsTableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->devicesSettingsTableWidget->columnCount(); j++)
        {
            ui->devicesSettingsTableWidget->setItem(i, j, new QTableWidgetItem(devicesSettings[i][j]));
        }
    }
}

void MainWindow::setupCoordinatesDisplay()
{
    /*QStringList axisesLabels;
    std::vector< std::shared_ptr<Axis> > axises = machineTool->getMovementController()->getAxises();
    for(auto axis : axises)
    {
        axisesLabels.push_back(QString(QString::fromStdString(axis->getName()) + ": "));
    }
    ui->currentCoordinatesListWidget->clear();
    ui->currentCoordinatesListWidget->addItems(axisesLabels);

    ui->baseCoordinatesListWidget->clear();
    ui->baseCoordinatesListWidget->addItems(axisesLabels);

    ui->parkCoordinatesListWidget->clear();
    ui->parkCoordinatesListWidget->addItems(axisesLabels);*/
}

void MainWindow::updateSensorsDisplay()
{
    QStringList sensorsNames = mainWindowController->getSensorsNames();
    QList<QColor> sensorsLeds = mainWindowController->getSensorsLeds();

    ui->sensorsTableWidget->clear();
    ui->sensorsTableWidget->setRowCount(sensorsNames.size());
    ui->sensorsTableWidget->setVerticalHeaderLabels(sensorsNames);
    ui->sensorsTableWidget->setColumnCount(1);

    for(int i = 0; i < ui->sensorsTableWidget->rowCount(); i++)
    {
        ui->sensorsTableWidget->verticalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(sensorsLeds[i]);
        ui->sensorsTableWidget->setItem(i, 0, item);
    }
}

void MainWindow::updateDevicesPanel()
{
    QStringList onScreenDevicesNames = mainWindowController->getOnScreenDevicesNames();
    QList<bool> onScreenDevicesStates = mainWindowController->getOnScreenDevicesStates();

    ui->devicesListWidget->clear();

    for(int i = 0; i < onScreenDevicesNames.size(); i++)
    {
        QListWidgetItem* item = new QListWidgetItem();
        item->setText(onScreenDevicesNames[i]);
        if(onScreenDevicesStates[i])
        {
            item->setTextColor(SmlColors::white());
            item->setBackgroundColor(SmlColors::red());
        }
        else
        {
            item->setTextColor(SmlColors::gray());
            item->setBackgroundColor(SmlColors::white());
        }
        ui->devicesListWidget->addItem(item);
    }
}

void MainWindow::setupAxisesShortcuts()
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
    };

    for (auto i = shortcutsMap.begin(); i != shortcutsMap.end(); i++)
    {
        const char* shortcutKey = std::get<0>(*i);
        QPushButton* shortcutButton = std::get<1>(*i);
        const char* shortcutSlot = std::get<2>(*i);

        QShortcut* shortcut = new QShortcut(QKeySequence(shortcutKey), shortcutButton);
        connect(shortcut, SIGNAL(activated()), this, shortcutSlot);

        axisesShortcuts.push_back(shortcut);
    }
}

void MainWindow::setupEditorFileActionsPushButtons()
{
    connect(ui->newFilePushButton, SIGNAL(clicked(bool)), this, SLOT(on_create_action_triggered()));
    connect(ui->openFilePushButton, SIGNAL(clicked(bool)), this, SLOT(on_open_action_triggered()));
    connect(ui->saveFilePushButton, SIGNAL(clicked(bool)), this, SLOT(on_save_action_triggered()));
    connect(ui->saveFileAsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_saveas_action_triggered()));
    connect(ui->addPushButton, SIGNAL(clicked(bool)), this, SLOT(on_add_action_triggered()));
}

void MainWindow::setupPointsEditorWidgets()
{
    setupPointsEditorFields();
    setupPointsPushButtons();
    connect(mainWindowController, SIGNAL(pointsUpdated()), this, SLOT(updatePointsEditorWidgets()));
}

void MainWindow::updateDisplays()
{
    updateBatteryStatusDisplay();
    updateSensorsDisplay();
#ifdef Q_OS_WIN
    /*if(u1Manager != nullptr)
    {
        updateMachineToolStatus();
        updateCoordinates();
    }*/
#endif
}

void MainWindow::deleteSelectedCommands(QModelIndexList indexes)
{
    std::vector<int> rows;
    for(auto index : indexes)
    {
        rows.push_back(index.row());
    }

    std::sort(rows.begin(), rows.begin() + rows.size());
    std::reverse(rows.begin(), rows.begin() + rows.size());

    for(auto row : rows)
    {
        mainWindowController->deleteCommand(row);
    }
}

void MainWindow::updateCoordinatesDisplay()
{
    /*MachineTool &i = MachineTool::Instance();

    Vector current = i.getCurrentCoordinates();
    Vector base = i.getBaseCoordinates();
    Vector park = i.getParkCoordinates();

<<<<<<< HEAD
    std::vector<std::pair<QListWidget*, Vector>> widgets = {
        { ui->listWidget_currentCoordinates, current },
        { ui->listWidget_baseCoordinates, base },
        { ui->listWidget_parkCoordinates, park }
=======
    std::vector<std::pair<QListWidget*, VectorDouble>> widgets = {
        { ui->currentCoordinatesListWidget, current },
        { ui->baseCoordinatesListWidget, base },
        { ui->parkCoordinatesListWidget, park }
>>>>>>> mvc
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

void MainWindow::updatePointsEditorFields()
{
    QList<QStringList> points = mainWindowController->getPoints();
    QList<SMLPointsTableWidget*> fields = { ui->pointsTableWidget, ui->pointsTableWidget_2 };
    QStringList axisesLabels = mainWindowController->getAxisesNames();

    for(auto field : fields)
    {
        field->clear();
        field->setColumnCount(axisesLabels.size());
        field->setHorizontalHeaderLabels(axisesLabels);
        field->setRowCount(points.size());

        for(int i = 0; i < points.size(); i++)
        {
            for(int j = 0; j < points[i].size(); j++)
            {
                field->setItem(i, j, new QTableWidgetItem(points[i][j]));
            }
        }
    }

    // растянуть таблицу с координатами редактора точек
    for(auto field : fields)
    {
        for (int i = 0; i < field->columnCount(); i++)
        {
            field->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        }
    }
}

void MainWindow::updatePointsEditorButtons()
{
    QList<QPushButton*> pointsActionsButtons =
    {
        ui->pointDeletePushButton,
        ui->pointDeletePushButton_2,
        ui->pointEditPushButton,
        ui->pointCopyPushButton,
        ui->pointCopyPushButton_2,
        ui->pointCursorPushButton,
        ui->pointCursorPushButton_2,
        ui->pointTransitionPushButton
    };

    if((ui->pointsTableWidget->rowCount() > 0) || (ui->pointsTableWidget_2->rowCount() > 0))
    {
        for(auto button : pointsActionsButtons)
        {
            button->setEnabled(true);
        }
    }
    else
    {
        for(auto button : pointsActionsButtons)
        {
            button->setEnabled(false);
        }
    }
}

void MainWindow::updateCommandsEditorWidgets()
{
    updateSMLCommandsTreeWidget();
}

void MainWindow::updateSMLCommandsTreeWidget()
{
    ui->smlEditorTreeWidget->clear();
    QList<QTreeWidgetItem *> items = mainWindowController->getCommands();
    ui->smlEditorTreeWidget->addTopLevelItems(items);

    for(int i = 0; i < ui->smlEditorTreeWidget->columnCount() - 1; i++)
    {
        ui->smlEditorTreeWidget->resizeColumnToContents(i);
    }
}

void MainWindow::updateBatteryStatusDisplay()
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

void MainWindow::updateVelocityPanel()
{
    int velocity = mainWindowController->getVelocity();
    ui->feedrateLcdNumber->display(QString::number(velocity));
    ui->feedrateScrollBar->setValue(velocity);
}

void MainWindow::updateSpindelRotationsPanel()
{
    int rotations = mainWindowController->getSpindelRotations();
    ui->rotationsLcdNumber->display(QString::number(rotations));
    ui->rotationsScrollBar->setValue(rotations);
}

void MainWindow::updateOptionsPanel()
{
    QStringList optionsNames = mainWindowController->getOptionsNames();
    ui->optionsListWidget->addItems(optionsNames);
}

void MainWindow::updateMachineToolStatusDisplay()
{
/*
#ifdef Q_OS_WIN
    ui->recievedDataTextEdit->clear();
    try
    {
        byte_array recieved = u1Manager->getU1()->receiveData(16);
        machineTool->getBuffer().updateBuffer(recieved);

        machineTool->getSensorsManager()->updateSensors(machineTool->getBuffer());
        updateSensorsField();

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
*/
}

void MainWindow::showMachineToolConnected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->showMessage("Machine Tool is connected");


    ui->devicesListWidget->setEnabled(true);
}

void MainWindow::showMachineToolDisconnected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
    ui->statusBar->showMessage("Machine Tool is disconnected");

    ui->devicesListWidget->setEnabled(false);
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
    for (auto i = axisesShortcuts.begin(); i != axisesShortcuts.end(); i++)
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
        ui->movementANegativePushButton
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
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
>>>>>>> mvc
    v.x = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble();
>>>>>>> mvc
    v.x = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementYPositivePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementYNegativePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativeYPositivePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.x = -1;
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXPositiveYPositivePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.x = 1;
    v.y = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXNegativeYNegativePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.x = -1;
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementXPositiveYNegativePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.x = 1;
    v.y = -1;

    i.stepMove(v);*/
}

void MainWindow::on_movementZPositivePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.z = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementZNegativePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.z = -1;

    i.stepMove(v);*/

}

void MainWindow::on_movementAPositivePushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
>>>>>>> mvc
    v.a = 1;

    i.stepMove(v);*/
}

void MainWindow::on_movementANegativePushButton_clicked()
{
<<<<<<< HEAD
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
=======
    /*MachineTool &i = MachineTool::Instance();
    VectorDouble v = VectorDouble() ;
    v.a = -1;

    i.stepMove(v);*/
>>>>>>> mvc
}

void MainWindow::on_feedrateScrollBar_valueChanged(int value)
{
    mainWindowController->updateVelocity(value);
    updateVelocityPanel();
}

void MainWindow::on_rotationsScrollBar_valueChanged(int value)
{
    mainWindowController->updateSpindelRotations(value);
    updateSpindelRotationsPanel();
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
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v = i.getBaseCoordinates();
    i.setParkCoordinates(v);
}
=======
>>>>>>> mvc

}

void MainWindow::on_zeroPushButton_clicked()
{
<<<<<<< HEAD
    MachineTool &i = MachineTool::Instance();
    Vector v = Vector();
    v = i.getBaseCoordinates();
    i.setNewZeroCoordinates(v);
}
=======
>>>>>>> mvc

}

void MainWindow::on_pointAddPushButton_clicked()
{
    addPoint();
}

void MainWindow::on_pointDeletePushButton_clicked()
{
    QItemSelectionModel *select;
    if(ui->editorTab->isVisible())
    {
        select = ui->pointsTableWidget_2->selectionModel();
    }
    else
    {
        if(ui->adjustmentTab->isVisible())
        {
            select = ui->pointsTableWidget->selectionModel();
        }
        else
        {
            return;
        }
    }


    QModelIndexList selectedItemsIndexes = select->selectedIndexes();

    if(selectedItemsIndexes.size() > 0)
    {
        QModelIndexList selectedRowsIndexes = SMLPointsTableWidget::getRowsIndexes(selectedItemsIndexes);
        deletePoints(selectedRowsIndexes);
    }
}

void MainWindow::on_pointCursorPushButton_clicked()
{
    SMLPointsTableWidget* currentTableWidget;
    if(ui->editorTab->isVisible())
    {
        currentTableWidget = ui->pointsTableWidget_2;
    }
    else
    {
        if(ui->adjustmentTab->isVisible())
        {
            currentTableWidget = ui->pointsTableWidget;
        }
        else
        {
            return;
        }
    }
    if(currentTableWidget->rowCount() > 0)
    {
        ToSelectionPointDialog(currentTableWidget, this).exec();
    }
}

void MainWindow::on_pointEditPushButton_clicked()
{
    QItemSelectionModel *select;
    if(ui->editorTab->isVisible())
    {
        select = ui->pointsTableWidget_2->selectionModel();
    }
    else
    {
        if(ui->adjustmentTab->isVisible())
        {
            select = ui->pointsTableWidget->selectionModel();
        }
        else
        {
            return;
        }
    }

    if(select->hasSelection())
    {
         editPoint(select->currentIndex());
    }
    else
    {
         QMessageBox(QMessageBox::Information, "Сообщение", QString("Точка не выбрана")).exec();
    }
}

void MainWindow::on_pointCopyPushButton_clicked()
{
    QItemSelectionModel *select;
    if(ui->editorTab->isVisible())
    {
        select = ui->pointsTableWidget_2->selectionModel();
    }
    else
    {
        if(ui->adjustmentTab->isVisible())
        {
            select = ui->pointsTableWidget->selectionModel();
        }
        else
        {
            return;
        }
    }

    QModelIndexList selectedItemsIndexes = select->selectedIndexes();
    if(selectedItemsIndexes.size() > 0)
    {
        QModelIndexList selectedRowsIndexes = SMLPointsTableWidget::getRowsIndexes(selectedItemsIndexes);

        for(auto row : selectedRowsIndexes)
        {
            QStringList pointsArguments = mainWindowController->getPoint(row.row());
            mainWindowController->addPoint(pointsArguments);
        }
    }
    else
    {
        return;
    }
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

void MainWindow::addPoint()
{
    AddPointDialog(mainWindowController, this).exec();
}

void MainWindow::editPoint(QModelIndex index)
{
    try
    {
        AddPointDialog(mainWindowController, index.row(), this).exec();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindow::deletePoints(QModelIndexList indexes)
{
    for(int i = indexes.size() - 1; i >= 0; i--)
    {
        mainWindowController->deletePoint(indexes[i].row());
    }
}

void MainWindow::on_toBasePushButton_clicked()
{

}

void MainWindow::on_open_action_triggered()
{
    mainWindowController->openSMLFile();
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

void MainWindow::on_viewPushButton_clicked()
{
    ProgramVisualizeWindow(mainWindowController, this).exec();
}

void MainWindow::on_smlEditorTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(column != 1)
    {
        column = 1;
    }
    QString commandName = item->text(column);
    int commandNumber = mainWindowController->getCommandId(commandName);

    unsigned int currentCommandNumber = item->text(0).toUInt() - 1;
    switch (commandNumber) {
    case CMD_SWITCH_ON:
        OnDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_SWITCH_OFF:
        OffDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_COMMENT:
        CommentDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_PAUSE:
        PauseDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_LINE:
        LineDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_ARC:
        ArcDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_TTLINE:
        TTLineDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_VARIABLE:
        SMLVariableDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    default:
        QMessageBox(QMessageBox::Warning, "Ошибка", "Выбранная команда не может быть отредактирована").exec();
        break;
    }
}

void MainWindow::commandsCopySlot()
{
    qDebug() << "Copy signal received";
}

void MainWindow::commandsCutSlot()
{
    qDebug() << "Cut signal received";
}

void MainWindow::commandsPasteSlot()
{
    qDebug() << "Paste signal received";
}

void MainWindow::commandsUndoSlot()
{
<<<<<<< HEAD
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
=======
    qDebug() << "Undo signal received";
>>>>>>> mvc
}

void MainWindow::on_commandsToolsListWidget_clicked(const QModelIndex &index)
{
    QString commandName = index.data().toString();
    int commandNumber = mainWindowController->getCommandId(commandName);

<<<<<<< HEAD
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
=======
    size_t currentCommandNumber = mainWindowController->getCommandsCount();
>>>>>>> mvc

    QList<QTreeWidgetItem*> selectedItems = ui->smlEditorTreeWidget->selectedItems();
    if(selectedItems.size() > 0)
    {
        currentCommandNumber = selectedItems[0]->text(0).toInt()-1;
    }

    switch (commandNumber) {
    case CMD_SWITCH_ON:
        OnDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_SWITCH_OFF:
        OffDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_COMMENT:
        CommentDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_PAUSE:
        PauseDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_LINE:
        LineDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_ARC:
        ArcDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_TTLINE:
        TTLineDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_VARIABLE:
        SMLVariableDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    default:
        QMessageBox(QMessageBox::Warning, "Ошибка", "Неизвестная команда").exec();
        break;
    }
}

void MainWindow::on_devicesListWidget_clicked(const QModelIndex &index)
{
<<<<<<< HEAD
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

void MainWindow::dimensionsFromMachineTool()
{
    MachineTool &instance = MachineTool::Instance();
    Vector v = instance.getDimensions();
    ui->x_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.x)));
    ui->y_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.y)));
    ui->z_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.z)));
    ui->a_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.a)));
    ui->b_dimension_lineEdit->setText(QString::fromStdString(std::to_string(v.b)));
}
void MainWindow::directionsFromMachineTool()
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
=======
    QString deviceName = index.data().toString();
    mainWindowController->switchDevice(deviceName);
    updateDevicesPanel();
>>>>>>> mvc
}

void MainWindow::on_add_action_triggered()
{
<<<<<<< HEAD
    MachineTool &instance = MachineTool::Instance();
    std::vector<AxisKFlopSettings> tmp = instance.getAxisKFlopSettings();
=======
    mainWindowController->addSMLFile();
>>>>>>> mvc
}

void MainWindow::on_create_action_triggered()
{
    mainWindowController->newSMLFile();
}

void MainWindow::on_save_action_triggered()
{
    mainWindowController->saveSMLFile();
}

void MainWindow::on_saveas_action_triggered()
{
    mainWindowController->saveSMLFileAs();
}

void MainWindow::on_connectCommandLinkButton_clicked()
{
    LogDialog(this).exec();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // окно на весь экран
    QMainWindow::showMaximized();

    // настройка контроллера
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
    connect(ui->importSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_importsettings_action_triggered()));
    connect(ui->exportSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_savesettings_action_triggered()));
}

void MainWindow::setupWidgets()
{
    // задаем горячие клавиши
    setupAxisesShortcuts();
    // проводим настройку необходимых виджетов
    setupStatusBar();
    setupDisplays();
    setupCommandsEditorField();
    setupGCodesEditorField();
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
    connect(mainWindowController, SIGNAL(commandsUpdated()), this, SLOT(updateSMLCommandsTreeWidget()));
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

void MainWindow::setupGCodesEditorField()
{
    connect(mainWindowController, SIGNAL(gcodesUpdated()), this, SLOT(updateGCodesEditorWidget()));
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
    updatePointsEditorFields();
    updatePointsEditorButtons();
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
    updateCoordinatesDisplays();
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

void MainWindow::updateCoordinatesDisplays()
{
    QList<Point> machineToolCoordinates = mainWindowController->getMachineToolCoordinates();

    if(machineToolCoordinates.length() >= 3)
    {
        Point currentCoordinates(machineToolCoordinates[0]);
        Point currentCoordinatesFromBase(machineToolCoordinates[1]);
        Point parkCoordinates(machineToolCoordinates[2]);

        showCoordinates(ui->currentCoordinatesListWidget, currentCoordinates);
        showCoordinates(ui->baseCoordinatesListWidget, currentCoordinatesFromBase);
        showCoordinates(ui->parkCoordinatesListWidget, parkCoordinates);
    }
}

void MainWindow::showCoordinates(QListWidget *display, Point coordinates)
{
    display->clear();
    for(size_t i = 0; i < coordinates.size(); i++)
    {
        QString axisKey = QString::fromStdString(axisesNames.getNameByKey(i));
        QString axisLabel = axisKey + QString(": ") + QString::number(coordinates[i], 'f', 3);
        display->addItem(axisLabel);
    }
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
    updateGCodesEditorWidget();
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

void MainWindow::updateGCodesEditorWidget()
{
    QString content = mainWindowController->getGCodesFileContent();
    ui->gcodesEditorTextEdit->setText(content);
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

}

void MainWindow::on_zeroPushButton_clicked()
{

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
    if(ui->smlEditorTab->isVisible())
    {
        mainWindowController->openSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            mainWindowController->openGCodesFile();
        }
    }
}


void MainWindow::on_gcodesEditorTextEdit_textChanged()
{
    QString text = ui->gcodesEditorTextEdit->toPlainText();
}

void MainWindow::on_importsettings_action_triggered()
{
    mainWindowController->importSettings();
}

void MainWindow::on_savesettings_action_triggered()
{
    mainWindowController->exportSettings();
}

void MainWindow::on_viewPushButton_clicked()
{
    mainWindowController->updateGCodes(ui->gcodesEditorTextEdit->toPlainText());
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
        SMLSwitchOnDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_SWITCH_OFF:
        SMLSwitchOffDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_COMMENT:
        SMLCommentDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_PAUSE:
        SMLPauseDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_LINE:
        LineDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_ARC:
        ArcDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_TTLINE:
        SMLTTLineDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_VARIABLE:
        SMLVariableDialog(mainWindowController, currentCommandNumber, this, true).exec();
        break;
    case CMD_TTTARC:
        SMLTTTArcDialog(mainWindowController, currentCommandNumber, this, true).exec();
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
    qDebug() << "Undo signal received";
}

void MainWindow::on_commandsToolsListWidget_clicked(const QModelIndex &index)
{
    QString commandName = index.data().toString();
    int commandNumber = mainWindowController->getCommandId(commandName);

    size_t currentCommandNumber = mainWindowController->getCommandsCount();

    QList<QTreeWidgetItem*> selectedItems = ui->smlEditorTreeWidget->selectedItems();
    if(selectedItems.size() > 0)
    {
        currentCommandNumber = selectedItems[0]->text(0).toInt()-1;
    }

    switch (commandNumber) {
    case CMD_SWITCH_ON:
        SMLSwitchOnDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_SWITCH_OFF:
        SMLSwitchOffDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_COMMENT:
        SMLCommentDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_PAUSE:
        SMLPauseDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_LINE:
        LineDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_ARC:
        ArcDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_TTLINE:
        SMLTTLineDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_VARIABLE:
        SMLVariableDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    case CMD_TTTARC:
        SMLTTTArcDialog(mainWindowController, currentCommandNumber, this).exec();
        break;
    default:
        QMessageBox(QMessageBox::Warning, "Ошибка", "Неизвестная команда").exec();
        break;
    }
}

void MainWindow::on_devicesListWidget_clicked(const QModelIndex &index)
{
    QString deviceName = index.data().toString();
    mainWindowController->switchDevice(deviceName);
    updateDevicesPanel();
}

void MainWindow::on_add_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        mainWindowController->addSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            mainWindowController->addGCodesFile(ui->gcodesEditorTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_create_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        mainWindowController->newSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            mainWindowController->newGCodesFile();
        }
    }
}

void MainWindow::on_save_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        mainWindowController->saveSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            mainWindowController->saveGCodesFile(ui->gcodesEditorTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_saveas_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        mainWindowController->saveSMLFileAs();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            mainWindowController->saveGCodesFileAs(ui->gcodesEditorTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_connectCommandLinkButton_clicked()
{
    LogDialog(this).exec();
}

void MainWindow::on_runCommandLinkButton_clicked()
{
    QString content = ui->gcodesEditorTextEdit->toPlainText();
    mainWindowController->parseGCodes(content);
}

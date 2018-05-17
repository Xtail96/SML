#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_machineTool(new MachineTool(this)),
    m_hightlighter(new GCodesSyntaxHighlighter(this))
{
    ui->setupUi(this);

    // окно на весь экран
    QMainWindow::showMaximized();

    setupMachineTool();

    // настройка виджетов
    setupWidgets();

    hideWidgets();

    updateAxisesBoard();
    updateDevicesBoard();
    updateSensorsBoard();

    updatePointsEditorFields();
    updateVelocityPanel();
    updateSpindelRotationsPanel();
    updateOptionsPanel();
    updateDevicesPanel();
    updateServerPanel();

    updateU1Displays();
    updateU2Displays();

    onU1Disconnected();
    onU2Disconnected();
}

MainWindow::~MainWindow()
{
    // удаляем горячие клавиши
    while (m_axisesShortcuts.size() > 0)
    {
        delete m_axisesShortcuts.back();
        m_axisesShortcuts.pop_back();
    }

    delete ui;
}

void MainWindow::setupMachineTool()
{
    connect(m_machineTool.data(), SIGNAL(u1Connected()), this, SLOT(onU1Connected()));
    connect(m_machineTool.data(), SIGNAL(u1Disconnected()), this, SLOT(onU1Disconnected()));
    connect(m_machineTool.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1Displays()));

    connect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(onU2Connected()));
    connect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(onU2Disconnected()));
    connect(m_machineTool.data(), SIGNAL(u2StateIsChanged()), this, SLOT(updateU1Displays()));

    connect(m_machineTool.data(), SIGNAL(u1Connected()), this, SLOT(updateServerPanel()));
    connect(m_machineTool.data(), SIGNAL(u1Disconnected()), this, SLOT(updateServerPanel()));
    connect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(updateServerPanel()));
    connect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(updateServerPanel()));

    connect(m_machineTool.data(), SIGNAL(gcodesUpdated()), this, SLOT(updateGCodesEditorWidget()));
    connect(m_machineTool.data(), SIGNAL(filePathUpdated()), this, SLOT(updateFilePath()));
    connect(m_machineTool.data(), SIGNAL(pointsUpdated()), this, SLOT(updatePointsEditorWidgets()));
}

void MainWindow::setupWidgets()
{
    // задаем горячие клавиши
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

        m_axisesShortcuts.push_back(shortcut);
    }

    // проводим настройку виджетов


    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    // настройка контроля габаритов
    connect(ui->edgesControlCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateEdgesControlStatus()));
    updateEdgesControlStatus();

    // настройка дисплеев координат
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

    // настройка подсветки синтаксиса
    m_hightlighter->setDocument(ui->gcodesEditorPlainTextEdit->document());
    m_hightlighter->setPattern();

    // настройка импорта и экспорта настроек
    connect(ui->importSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_importsettings_action_triggered()));
    connect(ui->exportSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_savesettings_action_triggered()));

    // настройка редактора точек
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointsTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QList<SMLPointsTableWidget*> pointsEditorTableWidgets = {ui->pointsTableWidget, ui->pointsTableWidget_2};
    for(auto pointsEditorTableWidget : pointsEditorTableWidgets)
    {
        connect(pointsEditorTableWidget, SIGNAL(editSignal(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
        connect(pointsEditorTableWidget, SIGNAL(eraseSignal(QModelIndexList)), this, SLOT(deletePoints(QModelIndexList)));
        connect(pointsEditorTableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
    }
    connect(ui->pointAddPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointAddPushButton_clicked()));
    connect(ui->pointDeletePushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointDeletePushButton_clicked()));
    connect(ui->pointCursorPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCursorPushButton_clicked()));
    connect(ui->pointCopyPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCopyPushButton_clicked()));
    updatePointsEditorButtons();

    // настройка кнопок работы с файлами
    connect(ui->newFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_create_action_triggered()));
    connect(ui->openFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_open_action_triggered()));
    connect(ui->saveFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_save_action_triggered()));
    connect(ui->saveFileAsToolButton, SIGNAL(clicked(bool)), this, SLOT(on_saveas_action_triggered()));
    connect(ui->addFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_add_action_triggered()));
    connect(ui->viewToolButton, SIGNAL(clicked(bool)), this, SLOT(on_view_action_triggered()));
}

void MainWindow::updateSettingsBoards()
{
    updateAxisesBoard();
    updateSensorsBoard();
    updateDevicesBoard();
}

void MainWindow::updateAxisesBoard()
{
    QStringList axisesSettings = m_machineTool->getAxisesSettings();
    ui->axisesSettingsListWidget->addItems(axisesSettings);
}

void MainWindow::updateSensorsBoard()
{
    QStringList sensorsNames = m_machineTool->getSensorsLabels();
    QStringList sensorsParametrsNames = m_machineTool->getSensorParametrLabels();
    QList<QStringList> sensorsSettings = m_machineTool->getSensorsSettings();

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
    QStringList devicesNames = m_machineTool->getDevicesNames();
    QStringList devicesParametrsNames = m_machineTool->getDevicesParametrsNames();
    QList<QStringList> devicesSettings = m_machineTool->getDevicesSettings();

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

void MainWindow::updateServerPanel()
{
    ui->currentConnectionsListWidget->clear();
    QStringList connections = m_machineTool->getCurrentConnections();
    ui->currentConnectionsListWidget->addItems(connections);

    ui->serverPortLcdNumber->display(m_machineTool->getServerPort());
    ui->sensorsBufferSizeLcdNumber->display(m_machineTool->getSensorsBufferSize());
    ui->devicesBufferSizeLcdNumber->display(m_machineTool->getDevicesBufferSize());
}

void MainWindow::updatePointsEditorWidgets()
{
    updatePointsEditorFields();
    updatePointsEditorButtons();
}

void MainWindow::updateU1Displays()
{
    updateBatteryStatusDisplay();
    updateSensorsDisplay();
    updateDevicesLeds();
}

void MainWindow::updateSensorsDisplay()
{
    QStringList sensorsNames = m_machineTool->getSensorsLabels();
    QList<QColor> sensorsLeds = m_machineTool->getSensorsLeds();

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
    QStringList onScreenDevicesNames = m_machineTool->getOnScreenDevicesNames();
    QList<bool> onScreenDevicesStates = m_machineTool->getOnScreenDevicesStates();

    ui->devicesLedsListWidget->clear();
    ui->devicesButtonsListWidget->clear();

    for(int i = 0; i < onScreenDevicesNames.size(); i++)
    {
        QListWidgetItem* button = new QListWidgetItem();
        QListWidgetItem* led = new QListWidgetItem();
        button->setText(onScreenDevicesNames[i]);
        if(onScreenDevicesStates[i])
        {
            led->setBackgroundColor(SmlColors::red());
        }
        else
        {
            led->setBackgroundColor(SmlColors::white());
        }
        ui->devicesButtonsListWidget->addItem(button);
        ui->devicesLedsListWidget->addItem(led);
    }
}

void MainWindow::updateDevicesLeds()
{
    QList<bool> onScreenDevicesStates = m_machineTool->getOnScreenDevicesStates();

    ui->devicesLedsListWidget->clear();

    for(int i = 0; i < onScreenDevicesStates.size(); i++)
    {
        QListWidgetItem* led = new QListWidgetItem();
        if(onScreenDevicesStates[i])
        {
            led->setBackgroundColor(SmlColors::red());
        }
        else
        {
            led->setBackgroundColor(SmlColors::white());
        }
        ui->devicesLedsListWidget->addItem(led);
    }
}

void MainWindow::updateU2Displays()
{
    updateCoordinatesDisplays();
}

void MainWindow::updateCoordinatesDisplays()
{
    QList<Point> machineToolCoordinates = m_machineTool->getMachineToolCoordinates();

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
        QString axisKey = SML_AXISES_NAMES.getNameByKey(i);
        QString axisLabel = axisKey + QString(": ") + QString::number(coordinates[i], 'f', 3);
        display->addItem(axisLabel);
    }
}

void MainWindow::updatePointsEditorFields()
{
    QList<QStringList> points = m_machineTool->getPoints();
    QList<SMLPointsTableWidget*> fields = { ui->pointsTableWidget, ui->pointsTableWidget_2 };
    QStringList axisesLabels = m_machineTool->getAxisesNames();

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

void MainWindow::updateGCodesEditorWidget()
{
    QString data = m_machineTool->getGCodesFileContent();

    //QStringList content = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    // fix!
    //ui->gcodesEditorPlainTextEdit->document()->setPlainText(data);
    ui->gcodesEditorPlainTextEdit->setPlainText(data);
}

void MainWindow::updateFilePath()
{
    QString filePath = m_machineTool->getFilePath("gcodes");
    ui->filePathLineEdit->setText(filePath);
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
    int velocity = m_machineTool->getFeedrate();
    ui->feedrateLcdNumber->display(QString::number(velocity));
    ui->feedrateScrollBar->setValue(velocity);
}

void MainWindow::updateSpindelRotationsPanel()
{
    int rotations = m_machineTool->getSpindelRotations();
    ui->rotationsLcdNumber->display(QString::number(rotations));
    ui->rotationsScrollBar->setValue(rotations);
}

void MainWindow::updateOptionsPanel()
{
    QStringList optionsNames = m_machineTool->getOptionsNames();
    ui->optionsListWidget->addItems(optionsNames);
}

void MainWindow::hideWidgets()
{
    ui->smlEditorTreeWidget->setEnabled(false);
    ui->commandsToolsListWidget->setEnabled(false);
}

void MainWindow::onU1Connected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->showMessage("Связь с контроллером датчиков и устройств установлена");

    ui->devicesButtonsListWidget->setEnabled(true);
    ui->devicesLedsListWidget->setEnabled(true);

    ui->sensorsTableWidget->setEnabled(true);

    ui->rotationsScrollBar->setEnabled(true);
    ui->rotationsLcdNumber->setEnabled(true);

    ui->optionsListWidget->setEnabled(true);
}

void MainWindow::onU1Disconnected()
{
    ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
    ui->statusBar->showMessage("Отсутсвует связь с контролером датчиков и устройств");

    ui->devicesButtonsListWidget->setEnabled(false);
    ui->devicesLedsListWidget->setEnabled(false);
    ui->sensorsTableWidget->setEnabled(false);

    ui->rotationsScrollBar->setEnabled(false);
    ui->rotationsLcdNumber->setEnabled(false);

    ui->optionsListWidget->setEnabled(false);
}

void MainWindow::onU2Connected()
{
    ui->currentCoordinatesListWidget->setEnabled(true);
    ui->baseCoordinatesListWidget->setEnabled(true);
    ui->parkCoordinatesListWidget->setEnabled(true);
    ui->edgesControlCheckBox->setEnabled(true);

    ui->movementXNegativePushButton->setEnabled(true);
    ui->movementXPositivePushButton->setEnabled(true);
    ui->movementXNegativeYNegativePushButton->setEnabled(true);
    ui->movementXNegativeYPositivePushButton->setEnabled(true);
    ui->movementXPositiveYNegativePushButton->setEnabled(true);
    ui->movementXPositiveYPositivePushButton->setEnabled(true);
    ui->movementYNegativePushButton->setEnabled(true);
    ui->movementYPositivePushButton->setEnabled(true);

    ui->movementZNegativePushButton->setEnabled(true);
    ui->movementZPositivePushButton->setEnabled(true);

    ui->movementANegativePushButton->setEnabled(true);
    ui->movementAPositivePushButton->setEnabled(true);

    ui->movementBNegativePushButton->setEnabled(true);
    ui->movementBPositivePushButton->setEnabled(true);

    ui->movementCNegativePushButton->setEnabled(true);
    ui->movementCPositivePushButton->setEnabled(true);

    ui->movementDNegativePushButton->setEnabled(true);
    ui->movementDPositivePushButton->setEnabled(true);

    for(auto shortcut : m_axisesShortcuts)
    {
        shortcut->setEnabled(true);
    }

    ui->discreteRadioButton_1->setEnabled(true);
    ui->discreteRadioButton_2->setEnabled(true);
    ui->discreteRadioButton_3->setEnabled(true);
    ui->discreteRadioButton_4->setEnabled(true);
    ui->discreteRadioButton_5->setEnabled(true);

    ui->feedrateScrollBar->setEnabled(true);
    ui->feedrateLcdNumber->setEnabled(true);

    ui->toBasePushButton->setEnabled(true);
    ui->toZeroPushButton->setEnabled(true);
    ui->toParkPushButton->setEnabled(true);
    ui->zeroPushButton->setEnabled(true);
    ui->zeroSensorPushButton->setEnabled(true);
    ui->parkPushButton->setEnabled(true);

    ui->runCommandLinkButton->setEnabled(true);
    ui->stopCommandLinkButton->setEnabled(true);
}

void MainWindow::onU2Disconnected()
{
    ui->currentCoordinatesListWidget->setEnabled(false);
    ui->baseCoordinatesListWidget->setEnabled(false);
    ui->parkCoordinatesListWidget->setEnabled(false);
    ui->edgesControlCheckBox->setEnabled(false);

    ui->movementXNegativePushButton->setEnabled(false);
    ui->movementXPositivePushButton->setEnabled(false);
    ui->movementXNegativeYNegativePushButton->setEnabled(false);
    ui->movementXNegativeYPositivePushButton->setEnabled(false);
    ui->movementXPositiveYNegativePushButton->setEnabled(false);
    ui->movementXPositiveYPositivePushButton->setEnabled(false);
    ui->movementYNegativePushButton->setEnabled(false);
    ui->movementYPositivePushButton->setEnabled(false);

    ui->movementZNegativePushButton->setEnabled(false);
    ui->movementZPositivePushButton->setEnabled(false);

    ui->movementANegativePushButton->setEnabled(false);
    ui->movementAPositivePushButton->setEnabled(false);

    ui->movementBNegativePushButton->setEnabled(false);
    ui->movementBPositivePushButton->setEnabled(false);

    ui->movementCNegativePushButton->setEnabled(false);
    ui->movementCPositivePushButton->setEnabled(false);

    ui->movementDNegativePushButton->setEnabled(false);
    ui->movementDPositivePushButton->setEnabled(false);

    for(auto shortcut : m_axisesShortcuts)
    {
        shortcut->setEnabled(false);
    }

    ui->discreteRadioButton_1->setEnabled(false);
    ui->discreteRadioButton_2->setEnabled(false);
    ui->discreteRadioButton_3->setEnabled(false);
    ui->discreteRadioButton_4->setEnabled(false);
    ui->discreteRadioButton_5->setEnabled(false);

    ui->feedrateScrollBar->setEnabled(false);
    ui->feedrateLcdNumber->setEnabled(false);

    ui->toBasePushButton->setEnabled(false);
    ui->toZeroPushButton->setEnabled(false);
    ui->toParkPushButton->setEnabled(false);
    ui->zeroPushButton->setEnabled(false);
    ui->zeroSensorPushButton->setEnabled(false);
    ui->parkPushButton->setEnabled(false);

    ui->runCommandLinkButton->setEnabled(false);
    ui->stopCommandLinkButton->setEnabled(false);
}

void MainWindow::disableMovementButtonsShortcutsAutoRepeat()
{
    setMovementButtonsShortcutsAutoRepeat(false);
}

void MainWindow::enableMovementButtonsShortcutsAutoRepeat()
{
    setMovementButtonsShortcutsAutoRepeat(true);
}

void MainWindow::setMovementButtonsShortcutsAutoRepeat(bool state)
{
    for (auto i = m_axisesShortcuts.begin(); i != m_axisesShortcuts.end(); i++)
        (*i)->setAutoRepeat(state);
}

void MainWindow::setMovementButtonsRepeatAutoRepeat(bool state)
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

    disableMovementButtonsShortcutsAutoRepeat();
    setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    //MachineTool::Instance().setMovementStep(0.1);

    disableMovementButtonsShortcutsAutoRepeat();
    setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    //MachineTool::Instance().setMovementStep(1);

    disableMovementButtonsShortcutsAutoRepeat();
    setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    //MachineTool::Instance().setMovementStep(10);

    disableMovementButtonsShortcutsAutoRepeat();
    setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    //MachineTool::Instance().setMovementStep(0);

    enableMovementButtonsShortcutsAutoRepeat();
    setMovementButtonsRepeatAutoRepeat(true);
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
    m_machineTool->updateVelocity(value);
    updateVelocityPanel();
}

void MainWindow::on_rotationsScrollBar_valueChanged(int value)
{
    m_machineTool->updateSpindelRotations(value);
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
            QStringList pointsArguments = m_machineTool->getPoint(row.row());
            m_machineTool->addPoint(pointsArguments);
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
    AddPointDialog(*(m_machineTool.data()), this).exec();
}

void MainWindow::editPoint(QModelIndex index)
{
    try
    {
        AddPointDialog(*(m_machineTool.data()), index.row(), this).exec();
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
        m_machineTool->deletePoint(indexes[i].row());
    }
}

void MainWindow::on_open_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->openSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->openGCodesFile();
        }
    }
}

void MainWindow::on_gcodesEditorPlainTextEdit_textChanged()
{
    QString text = ui->gcodesEditorPlainTextEdit->toPlainText();
}

void MainWindow::on_importsettings_action_triggered()
{
    m_machineTool->importSettings();
}

void MainWindow::on_savesettings_action_triggered()
{
    m_machineTool->exportSettings();
}

void MainWindow::on_devicesButtonsListWidget_clicked(const QModelIndex &index)
{
    QString deviceName = index.data().toString();
    m_machineTool->switchDevice(deviceName);
}

void MainWindow::on_add_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->addSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->addGCodesFile(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_create_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->newSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->newGCodesFile();
        }
    }
}

void MainWindow::on_save_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->saveSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->saveGCodesFile(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_saveas_action_triggered()
{
    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->saveSMLFileAs();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->saveGCodesFileAs(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_runCommandLinkButton_clicked()
{
    QString content = ui->gcodesEditorPlainTextEdit->toPlainText();
    m_machineTool->parseGCodes(content);
}

void MainWindow::on_view_action_triggered()
{
    m_machineTool->updateGCodes(ui->gcodesEditorPlainTextEdit->toPlainText());
    on_save_action_triggered();
    //ProgramVisualizeWindow(mainWindowController, this).exec();
    //GCodesWebViewDialog(this).exec();

    CandleVisualizerDialog(m_machineTool->getFilePath(), this).exec();
}

void MainWindow::on_consoleOpenPushButton_clicked()
{
    SMLConsoleDialog(*(m_machineTool.data()), this).exec();
}

/*void MainWindow::deleteSelectedCommands(QModelIndexList indexes)
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
}*/

/*void MainWindow::on_smlEditorTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
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
}*/

/*void MainWindow::commandsCopySlot()
{
    qDebug() << "Copy signal received";
}*/

/*void MainWindow::commandsCutSlot()
{
    qDebug() << "Cut signal received";
}*/

/*void MainWindow::commandsPasteSlot()
{
    qDebug() << "Paste signal received";
}*/

/*void MainWindow::commandsUndoSlot()
{
    qDebug() << "Undo signal received";
}*/

/*void MainWindow::on_commandsToolsListWidget_clicked(const QModelIndex &index)
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
}*/

/*void MainWindow::updateCommandsEditorWidgets()
{
    updateSMLCommandsTreeWidget();
    updateGCodesEditorWidget();
}*/

/*void MainWindow::updateSMLCommandsTreeWidget()
{
    ui->smlEditorTreeWidget->clear();
    QList<QTreeWidgetItem *> items = mainWindowController->getCommands();
    ui->smlEditorTreeWidget->addTopLevelItems(items);

    for(int i = 0; i < ui->smlEditorTreeWidget->columnCount() - 1; i++)
    {
        ui->smlEditorTreeWidget->resizeColumnToContents(i);
    }
}*/

void MainWindow::on_edgesControlCheckBox_clicked()
{
    m_machineTool->setSoftLimitsMode(ui->edgesControlCheckBox->isChecked());
}

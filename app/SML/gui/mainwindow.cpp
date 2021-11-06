#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_slotsInfo(QList<QMetaObject::Connection>()),
    m_hightlighter(new GCodesSyntaxHighlighter(this)),
    m_adaptersLauncher(new AdaptersLauncher(this))
{
    ui->setupUi(this);

    this->setupWidgets();

    this->setupHardwareDriver();
    this->setupSlots();

    this->fillSettings();
    m_adaptersLauncher->startAdapters(true, true);
}

MainWindow::~MainWindow()
{
    this->resetSlots();
    delete ui;
}

void MainWindow::setupHardwareDriver()
{
    auto& driver = HardwareDriver::getInstance();

    auto hardwarePositionChangeHandler = [=](HARDWARE_EVENT_DATA)
    {
        auto& driver = HardwareDriver::getInstance();
        ui->currentCoordinatesListWidget->clear();
        ui->baseCoordinatesListWidget->clear();
        ui->parkCoordinatesListWidget->clear();

        if(!driver.isConnected()) return;

        auto axes = driver.getMotionController().axes();
        QStringList currentCoordinatesFromZero = {};
        QStringList currentCoordinatesFromBase = {};
        QStringList parkCoordinates = {};
        for(auto axis : axes)
        {
            currentCoordinatesFromZero.append(axis.decoratedId() + ": "
                                            + QString::number(axis.currentPositionFromZero(), 'f', 3));
            currentCoordinatesFromBase.append(axis.decoratedId() + ": "
                                            + QString::number(axis.currentPositionFromBase(), 'f', 3));
            parkCoordinates.append(axis.decoratedId() + ": " + QString::number(axis.parkPosition(), 'f', 3));
        }
        ui->currentCoordinatesListWidget->addItems(currentCoordinatesFromZero);
        ui->baseCoordinatesListWidget->addItems(currentCoordinatesFromBase);
        ui->parkCoordinatesListWidget->addItems(parkCoordinates);

    };

    auto hardwareConnectionStateChangedHandler = [=](HARDWARE_EVENT_DATA)
    {
        auto& driver = HardwareDriver::getInstance();
        bool isConnected = driver.isConnected();
        if(isConnected)
        {
            ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
            ui->statusBar->showMessage("Hardware driver is ready");
            this->setAxesButtonsState(true);
            this->setAdjustmentActionsButtonsState(true);
            hardwarePositionChangeHandler(HARDWARE_EVENT_DATA());
        }
        else
        {
            ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
            ui->statusBar->showMessage("Hardware driver is not ready");
            this->setAxesButtonsState(false);
            this->setAdjustmentActionsButtonsState(false);
            ui->currentCoordinatesListWidget->clear();
            ui->baseCoordinatesListWidget->clear();
            ui->parkCoordinatesListWidget->clear();
        }
    };

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, hardwareConnectionStateChangedHandler);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, hardwareConnectionStateChangedHandler);

    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, hardwareConnectionStateChangedHandler);
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, hardwareConnectionStateChangedHandler);

    driver.registerHandler(HARDWARE_EVENT::CurrentPositionChanged, hardwarePositionChangeHandler);
}

void MainWindow::setupWidgets()
{
    this->hideWidgets();

    // изменяет TitleBar для DockWidget
    ui->dashboardDockWidget->setTitleBarWidget(new QWidget(ui->dashboardDockWidget));

    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("Application initialization.."));

    // настройка редактора точек
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->spindelsListWidget->setStyleSheet("QListWidget { background-color: transparent; }");
    ui->supportDevicesListWidget->setStyleSheet("QListWidget { background-color: transparent; }");
    ui->optionsListWidget->setStyleSheet("QListWidget { background-color: transparent; }");

    SettingsManager s;
    QStringList keys = s.settingsKeys();

    ui->settingsTableWidget->setColumnCount(1);
    ui->settingsTableWidget->setRowCount(keys.length());

    ui->settingsTableWidget->setHorizontalHeaderLabels({"Значения настроек"});
    ui->settingsTableWidget->setVerticalHeaderLabels(keys);
    ui->settingsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->setAxesButtonsState(false);
    this->setAdjustmentActionsButtonsState(false);
    ui->discreteRadioButton_5->click();
}

void MainWindow::setupSlots()
{
    m_slotsInfo.append(QObject::connect(new QShortcut(QKeySequence("Esc"), this), &QShortcut::activated, this, [=]() {
        switch (ui->mainTabMenu->currentIndex()) {
        case 0:
            ui->mainTabMenu->setCurrentIndex(1);
            break;
        case 1:
            ui->mainTabMenu->setCurrentIndex(0);
            break;
        default:
            ui->mainTabMenu->setCurrentIndex(1);
            break;
        }
    }));

    m_slotsInfo.append(QObject::connect(new QShortcut(QKeySequence("Space"), this), &QShortcut::activated, this, [=]() {
        if(ui->mainTabMenu->currentIndex() == 1)
        {
            qInfo() << "Space pressed. Stop moving";
            HardwareDriver::getInstance().stopMoving();
        }
    }));

    // Настройка горячих клавиш для основных осей координат.
    ui->movementXNegativeYPositivePushButton->bindAxis(Axis::Id::X);
    ui->movementXNegativeYPositivePushButton->bindAxis(Axis::Id::Y);
    ui->movementXNegativeYPositivePushButton->bindShortcut(Qt::Key_Q);
    ui->movementXNegativeYPositivePushButton->bindShortcut(QKeySequence("Й"));

    ui->movementYPositivePushButton->bindAxis(Axis::Id::Y);
    ui->movementYPositivePushButton->bindShortcut(Qt::Key_W);
    ui->movementYPositivePushButton->bindShortcut(QKeySequence("Ц"));

    ui->movementXPositiveYPositivePushButton->bindAxis(Axis::Id::X);
    ui->movementXPositiveYPositivePushButton->bindAxis(Axis::Id::Y);
    ui->movementXPositiveYPositivePushButton->bindShortcut(Qt::Key_E);
    ui->movementXPositiveYPositivePushButton->bindShortcut(QKeySequence("У"));

    ui->movementXNegativePushButton->bindAxis(Axis::Id::X);
    ui->movementXNegativePushButton->bindShortcut(Qt::Key_A);
    ui->movementXNegativePushButton->bindShortcut(QKeySequence("Ф"));

    ui->movementXPositivePushButton->bindAxis(Axis::Id::X);
    ui->movementXPositivePushButton->bindShortcut(Qt::Key_D);
    ui->movementXPositivePushButton->bindShortcut(QKeySequence("В"));

    ui->movementXNegativeYNegativePushButton->bindAxis(Axis::Id::X);
    ui->movementXNegativeYNegativePushButton->bindAxis(Axis::Id::Y);
    ui->movementXNegativeYNegativePushButton->bindShortcut(Qt::Key_Z);
    ui->movementXNegativeYNegativePushButton->bindShortcut(QKeySequence("Я"));

    ui->movementYNegativePushButton->bindAxis(Axis::Id::Y);
    ui->movementYNegativePushButton->bindShortcut(Qt::Key_S);
    ui->movementYNegativePushButton->bindShortcut(QKeySequence("Ы"));

    ui->movementXPositiveYNegativePushButton->bindAxis(Axis::Id::X);
    ui->movementXPositiveYNegativePushButton->bindAxis(Axis::Id::Y);
    ui->movementXPositiveYNegativePushButton->bindShortcut(Qt::Key_X);
    ui->movementXPositiveYNegativePushButton->bindShortcut(QKeySequence("Ч"));

    ui->movementZPositivePushButton->bindAxis(Axis::Id::Z);
    ui->movementZPositivePushButton->bindShortcut(Qt::Key_Up);

    ui->movementZNegativePushButton->bindAxis(Axis::Id::Z);
    ui->movementZNegativePushButton->bindShortcut(Qt::Key_Down);

    // Настройка горячих клавиш для дополнительных осей координат.
    ui->movementANegativePushButton->bindAxis(Axis::Id::A);
    ui->movementANegativePushButton->bindShortcut(Qt::Key_Left);

    ui->movementAPositivePushButton->bindAxis(Axis::Id::A);
    ui->movementAPositivePushButton->bindShortcut(Qt::Key_Right);

    ui->movementBNegativePushButton->bindAxis(Axis::Id::B);
    ui->movementBNegativePushButton->bindShortcut(Qt::SHIFT + Qt::Key_Left);

    ui->movementBPositivePushButton->bindAxis(Axis::Id::B);
    ui->movementBPositivePushButton->bindShortcut(Qt::SHIFT + Qt::Key_Right);

    ui->movementCNegativePushButton->bindAxis(Axis::Id::C);
    ui->movementCNegativePushButton->bindShortcut(Qt::ALT + Qt::Key_Left);

    ui->movementCPositivePushButton->bindAxis(Axis::Id::C);
    ui->movementCPositivePushButton->bindShortcut(Qt::ALT + Qt::Key_Right);

    // Настройка горячих клавиш для вспомогательных осей координат.
    ui->movementUNegativePushButton->bindAxis(Axis::Id::U);
    ui->movementUNegativePushButton->bindShortcut(Qt::SHIFT + Qt::Key_A);
    ui->movementUNegativePushButton->bindShortcut(QKeySequence("Shift+Ф"));

    ui->movementUPositivePushButton->bindAxis(Axis::Id::U);
    ui->movementUPositivePushButton->bindShortcut(Qt::SHIFT + Qt::Key_D);
    ui->movementUPositivePushButton->bindShortcut(QKeySequence("Shift+В"));

    ui->movementVNegativePushButton->bindAxis(Axis::Id::V);
    ui->movementVNegativePushButton->bindShortcut(Qt::SHIFT + Qt::Key_S);
    ui->movementVNegativePushButton->bindShortcut(QKeySequence("Shift+Ы"));

    ui->movementVPositivePushButton->bindAxis(Axis::Id::V);
    ui->movementVPositivePushButton->bindShortcut(Qt::SHIFT + Qt::Key_W);
    ui->movementVPositivePushButton->bindShortcut(QKeySequence("Shift+Ц"));

    ui->movementWNegativePushButton->bindAxis(Axis::Id::W);
    ui->movementWNegativePushButton->bindShortcut(Qt::SHIFT + Qt::Key_Down);

    ui->movementWPositivePushButton->bindAxis(Axis::Id::W);
    ui->movementWPositivePushButton->bindShortcut(Qt::SHIFT + Qt::Key_Up);
}

void MainWindow::resetSlots()
{
    for(auto& slotInfo : m_slotsInfo)
    {
        QObject::disconnect(slotInfo);
    }
    m_slotsInfo.clear();
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

void MainWindow::hideWidgets()
{
    ui->smlEditorTab->setEnabled(false);
}

void MainWindow::on_exit_action_triggered()
{
    exit(0);
}

void MainWindow::on_syntaxHighlightingCheckBox_clicked()
{
    if(ui->syntaxHighlightingCheckBox->isChecked())
    {
        // настройка подсветки синтаксиса
        m_hightlighter->setDocument(ui->gcodesEditorPlainTextEdit->document());
        m_hightlighter->setPattern();
    }
    else
    {
        m_hightlighter->setDocument(nullptr);
        m_hightlighter->setPattern();
    }
}

void MainWindow::on_saveSettingsPushButton_clicked()
{
    SettingsManager s;
    for(int i = 0; i < ui->settingsTableWidget->rowCount(); i++)
    {
        auto header = ui->settingsTableWidget->verticalHeaderItem(i)->text();
        QString group = header.split("/").first();
        QString key = header.split("/").last();

        QString value = ui->settingsTableWidget->item(i, 0)->text();
        s.set(group, key, value);
    }
}

void MainWindow::fillSettings()
{
    SettingsManager s;
    for(int i = 0; i < ui->settingsTableWidget->rowCount(); i++)
    {
        auto header = ui->settingsTableWidget->verticalHeaderItem(i)->text();
        QString group = header.split("/").first();
        QString key = header.split("/").last();

        QString value = s.get(group, key).toString();
        ui->settingsTableWidget->setItem(i, 0, new QTableWidgetItem(value));
    }
}

QList<AxisPushButton *> MainWindow::getAllAxesButtons()
{
    return {
        ui->movementXNegativePushButton,
        ui->movementXPositivePushButton,
        ui->movementYNegativePushButton,
        ui->movementYPositivePushButton,
        ui->movementXNegativeYNegativePushButton,
        ui->movementXNegativeYPositivePushButton,
        ui->movementXPositiveYNegativePushButton,
        ui->movementXPositiveYPositivePushButton,
        ui->movementZNegativePushButton,
        ui->movementZPositivePushButton,
        ui->movementANegativePushButton,
        ui->movementAPositivePushButton,
        ui->movementBNegativePushButton,
        ui->movementBPositivePushButton,
        ui->movementCNegativePushButton,
        ui->movementCPositivePushButton,
        ui->movementUNegativePushButton,
        ui->movementUPositivePushButton,
        ui->movementVNegativePushButton,
        ui->movementVPositivePushButton,
        ui->movementWNegativePushButton,
        ui->movementWPositivePushButton
    };
}

void MainWindow::setAxesButtonsState(bool enable)
{
    auto& driver = HardwareDriver::getInstance();
    auto& motionContoller = driver.getMotionController();

    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
    {
        if(enable)
        {
            bool axisExists = true;
            for(auto axisId : button->getAxes())
            {
                if(!motionContoller.axisExists(axisId))
                    axisExists = false;
            }
            if(axisExists)
                button->setEnabled(true);
        }
        else
        {
            button->setEnabled(false);
        }

    }
}

void MainWindow::setAdjustmentActionsButtonsState(bool enable)
{
    auto buttons = {
        ui->toBasePushButton,
        ui->zeroPushButton,
        ui->toZeroPushButton,
        ui->zeroSensorPushButton,
        ui->parkPushButton,
        ui->toParkPushButton,
        ui->runPushButton
    };
    for(auto button : buttons)
        button->setEnabled(enable);
}

void MainWindow::stopContiniousMovement()
{
    if(m_stepSize < INF_MOVE)
        return;

    auto& driver = HardwareDriver::getInstance();
    if(driver.isMoving())
        driver.stopMoving();
}

void MainWindow::on_movementXPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize}});
}

void MainWindow::on_movementXPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementXNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize}});
}

void MainWindow::on_movementXNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementYPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementYNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementXNegativeYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize},
                       {Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementXNegativeYPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementXNegativeYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize},
                       {Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementXNegativeYNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementXPositiveYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize},
                       {Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementXPositiveYPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementXPositiveYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize},
                       {Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementXPositiveYNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementZPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Z, m_stepSize}});
}

void MainWindow::on_movementZPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementZNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Z, -m_stepSize}});
}

void MainWindow::on_movementZNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementANegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::A, -m_stepSize}});
}

void MainWindow::on_movementANegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementAPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::A, m_stepSize}});
}

void MainWindow::on_movementAPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementBNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::B, -m_stepSize}});
}

void MainWindow::on_movementBNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementBPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::B, m_stepSize}});
}

void MainWindow::on_movementBPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementCNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::C, -m_stepSize}});
}

void MainWindow::on_movementCNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementCPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::C, m_stepSize}});
}

void MainWindow::on_movementCPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementUNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::U, -m_stepSize}});
}

void MainWindow::on_movementUNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementUPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::U, m_stepSize}});
}

void MainWindow::on_movementUPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementVNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::V, -m_stepSize}});
}

void MainWindow::on_movementVNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementVPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::V, m_stepSize}});
}

void MainWindow::on_movementVPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementWNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::W, -m_stepSize}});
}

void MainWindow::on_movementWNegativePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_movementWPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::W, m_stepSize}});
}

void MainWindow::on_movementWPositivePushButton_released()
{
    this->stopContiniousMovement();
}

void MainWindow::on_discreteRadioButton_1_clicked()
{
    m_stepSize = 0.01;
    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
        button->setContiniousMovement(false);
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    m_stepSize = 0.1;
    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
        button->setContiniousMovement(false);
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    m_stepSize = 1;
    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
        button->setContiniousMovement(false);
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    m_stepSize = 10;
    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
        button->setContiniousMovement(false);
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    m_stepSize = INF_MOVE;
    auto axesButtons = this->getAllAxesButtons();
    for(auto button : axesButtons)
        button->setContiniousMovement(true);
}

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
    m_slotsInfo.append(bindShortcut(ui->movementXNegativeYPositivePushButton, Qt::Key_Q));
    m_slotsInfo.append(bindShortcut(ui->movementXNegativeYPositivePushButton, QKeySequence("Й")));

    m_slotsInfo.append(bindShortcut(ui->movementYPositivePushButton, Qt::Key_W));
    m_slotsInfo.append(bindShortcut(ui->movementYPositivePushButton, QKeySequence("Ц")));

    m_slotsInfo.append(bindShortcut(ui->movementXPositiveYPositivePushButton, Qt::Key_E));
    m_slotsInfo.append(bindShortcut(ui->movementXPositiveYPositivePushButton, QKeySequence("У")));

    m_slotsInfo.append(bindShortcut(ui->movementXNegativePushButton, Qt::Key_A));
    m_slotsInfo.append(bindShortcut(ui->movementXNegativePushButton, QKeySequence("Ф")));

    m_slotsInfo.append(bindShortcut(ui->movementXPositivePushButton, Qt::Key_D));
    m_slotsInfo.append(bindShortcut(ui->movementXPositivePushButton, QKeySequence("В")));

    m_slotsInfo.append(bindShortcut(ui->movementXNegativeYNegativePushButton, Qt::Key_Z));
    m_slotsInfo.append(bindShortcut(ui->movementXNegativeYNegativePushButton, QKeySequence("Я")));

    m_slotsInfo.append(bindShortcut(ui->movementYNegativePushButton, Qt::Key_S));
    m_slotsInfo.append(bindShortcut(ui->movementYNegativePushButton, QKeySequence("Ы")));

    m_slotsInfo.append(bindShortcut(ui->movementXPositiveYNegativePushButton, Qt::Key_X));
    m_slotsInfo.append(bindShortcut(ui->movementXPositiveYNegativePushButton, QKeySequence("Ч")));

    m_slotsInfo.append(bindShortcut(ui->movementZPositivePushButton, Qt::Key_Up));
    m_slotsInfo.append(bindShortcut(ui->movementZNegativePushButton, Qt::Key_Down));


    // Настройка горячих клавиш для дополнительных осей координат.
    m_slotsInfo.append(bindShortcut(ui->movementANegativePushButton, Qt::Key_Left));
    m_slotsInfo.append(bindShortcut(ui->movementAPositivePushButton, Qt::Key_Right));
    m_slotsInfo.append(bindShortcut(ui->movementBNegativePushButton, Qt::SHIFT + Qt::Key_Left));
    m_slotsInfo.append(bindShortcut(ui->movementBPositivePushButton, Qt::SHIFT + Qt::Key_Right));
    m_slotsInfo.append(bindShortcut(ui->movementCNegativePushButton, Qt::ALT + Qt::Key_Left));
    m_slotsInfo.append(bindShortcut(ui->movementCPositivePushButton, Qt::ALT + Qt::Key_Right));


    // Настройка горячих клавиш для вспомогательных осей координат.
    m_slotsInfo.append(bindShortcut(ui->movementUNegativePushButton, Qt::SHIFT + Qt::Key_A));
    m_slotsInfo.append(bindShortcut(ui->movementUNegativePushButton, QKeySequence("Shift+Ф")));
    m_slotsInfo.append(bindShortcut(ui->movementUPositivePushButton, Qt::SHIFT + Qt::Key_D));
    m_slotsInfo.append(bindShortcut(ui->movementUPositivePushButton, QKeySequence("Shift+В")));

    m_slotsInfo.append(bindShortcut(ui->movementVNegativePushButton, Qt::SHIFT + Qt::Key_S));
    m_slotsInfo.append(bindShortcut(ui->movementVNegativePushButton, QKeySequence("Shift+Ы")));
    m_slotsInfo.append(bindShortcut(ui->movementVPositivePushButton, Qt::SHIFT + Qt::Key_W));
    m_slotsInfo.append(bindShortcut(ui->movementVPositivePushButton, QKeySequence("Shift+Ц")));

    m_slotsInfo.append(bindShortcut(ui->movementWNegativePushButton, Qt::SHIFT + Qt::Key_Down));
    m_slotsInfo.append(bindShortcut(ui->movementWPositivePushButton, Qt::SHIFT + Qt::Key_Up));
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

void MainWindow::setAxesButtonsState(bool enable)
{
    auto& driver = HardwareDriver::getInstance();
    auto& motionContoller = driver.getMotionController();

    auto axesButtons = {
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X}, ui->movementXNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X}, ui->movementXPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::Y}, ui->movementYNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::Y}, ui->movementYPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X, Axis::Id::Y}, ui->movementXNegativeYNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X, Axis::Id::Y}, ui->movementXNegativeYPositivePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X, Axis::Id::Y}, ui->movementXPositiveYNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::X, Axis::Id::Y}, ui->movementXPositiveYPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::Z}, ui->movementZNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::Z}, ui->movementZPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::A}, ui->movementANegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::A}, ui->movementAPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::B}, ui->movementBNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::B}, ui->movementBPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::C}, ui->movementCNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::C}, ui->movementCPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::U}, ui->movementUNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::U}, ui->movementUPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::V}, ui->movementVNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::V}, ui->movementVPositivePushButton),

        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::W}, ui->movementWNegativePushButton),
        QPair< QList<Axis::Id>, QPushButton*>({Axis::Id::W}, ui->movementWPositivePushButton)
    };

    for(auto button : axesButtons)
    {
        if(enable)
        {
            bool axisExists = true;
            for(auto axisId : button.first)
            {
                if(!motionContoller.axisExists(axisId))
                    axisExists = false;
            }
            if(axisExists)
                button.second->setEnabled(true);
        }
        else
        {
            button.second->setEnabled(false);
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

void MainWindow::on_movementXPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize}});
}

void MainWindow::on_movementXNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize}});
}

void MainWindow::on_movementYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementXNegativeYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize},
                       {Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementXNegativeYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, -m_stepSize},
                       {Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementXPositiveYPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize},
                       {Axis::Id::Y, m_stepSize}});
}

void MainWindow::on_movementXPositiveYNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::X, m_stepSize},
                       {Axis::Id::Y, -m_stepSize}});
}

void MainWindow::on_movementZPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Z, m_stepSize}});
}

void MainWindow::on_movementZNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::Z, -m_stepSize}});
}

void MainWindow::on_movementANegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::A, -m_stepSize}});
}

void MainWindow::on_movementAPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::A, m_stepSize}});
}

void MainWindow::on_movementBNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::B, -m_stepSize}});
}

void MainWindow::on_movementBPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::B, m_stepSize}});
}

void MainWindow::on_movementCNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::C, -m_stepSize}});
}

void MainWindow::on_movementCPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::C, m_stepSize}});
}

void MainWindow::on_movementUNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::U, -m_stepSize}});
}

void MainWindow::on_movementUPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::U, m_stepSize}});
}

void MainWindow::on_movementVNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::V, -m_stepSize}});
}

void MainWindow::on_movementVPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::V, m_stepSize}});
}

void MainWindow::on_movementWNegativePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::W, -m_stepSize}});
}

void MainWindow::on_movementWPositivePushButton_pressed()
{
    auto& driver = HardwareDriver::getInstance();
    driver.moveOffset({{Axis::Id::W, m_stepSize}});
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    m_stepSize = 10;
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    m_stepSize = 1;
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    m_stepSize = 0.1;
}

void MainWindow::on_discreteRadioButton_1_clicked()
{
    m_stepSize = 0.01;
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    m_stepSize = 0;
}

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
    this->hideWidgets();

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
    auto hardwareConnectionStateChangedHandler = [=]()
    {
        auto& driver = HardwareDriver::getInstance();
        bool isConnected = driver.isConnected();
        if(isConnected)
        {
            ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
            ui->statusBar->showMessage("Hardware driver is ready");

            this->enableUsedAxesButtons();

            auto axes = driver.getMotionController().axes();
            QStringList currentCoordinatesFromZero = {};
            QStringList currentCoordinatesFromBase = {};
            QStringList parkCoordinates = {};
            for(auto axis : axes)
            {
                currentCoordinatesFromZero.append(axis->decoratedId() + ": "
                                                + QString::number(axis->currentPositionFromZero(), 'f', 3));
                currentCoordinatesFromBase.append(axis->decoratedId() + ": "
                                                + QString::number(axis->currentPositionFromBase(), 'f', 3));
                parkCoordinates.append(axis->decoratedId() + ": " + QString::number(axis->parkPosition(), 'f', 3));
            }
            ui->currentCoordinatesListWidget->addItems(currentCoordinatesFromZero);
            ui->baseCoordinatesListWidget->addItems(currentCoordinatesFromBase);
            ui->parkCoordinatesListWidget->addItems(parkCoordinates);
        }
        else
        {
            ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
            ui->statusBar->showMessage("Hardware driver is not ready");

            this->disableAllAxesButtons();

            ui->currentCoordinatesListWidget->clear();
            ui->baseCoordinatesListWidget->clear();
            ui->parkCoordinatesListWidget->clear();
        }
    };

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnected, hardwareConnectionStateChangedHandler);
    driver.registerHandler(HARDWARE_EVENT::DeviceControllerDisconnected, hardwareConnectionStateChangedHandler);

    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnected, hardwareConnectionStateChangedHandler);
    driver.registerHandler(HARDWARE_EVENT::MotionControllerDisconnected, hardwareConnectionStateChangedHandler);
}

void MainWindow::setupWidgets()
{
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

    ui->settingsTableWidget->setHorizontalHeaderLabels({"Current Value"});
    ui->settingsTableWidget->setVerticalHeaderLabels(keys);
    ui->settingsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->disableAllAxesButtons();
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

void MainWindow::enableUsedAxesButtons()
{
    auto& driver = HardwareDriver::getInstance();
    auto& motionContoller = driver.getMotionController();

    auto axesButtons = {
        QPair< QList<AxisId>, QPushButton*>({AxisId::X}, ui->movementXNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::X}, ui->movementXPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::Y}, ui->movementYNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::Y}, ui->movementYPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::X, AxisId::Y}, ui->movementXNegativeYNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::X, AxisId::Y}, ui->movementXNegativeYPositivePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::X, AxisId::Y}, ui->movementXPositiveYNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::X, AxisId::Y}, ui->movementXPositiveYPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::Z}, ui->movementZNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::Z}, ui->movementZPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::A}, ui->movementANegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::A}, ui->movementAPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::B}, ui->movementBNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::B}, ui->movementBPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::C}, ui->movementCNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::C}, ui->movementCPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::U}, ui->movementUNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::U}, ui->movementUPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::V}, ui->movementVNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::V}, ui->movementVPositivePushButton),

        QPair< QList<AxisId>, QPushButton*>({AxisId::W}, ui->movementWNegativePushButton),
        QPair< QList<AxisId>, QPushButton*>({AxisId::W}, ui->movementWPositivePushButton)
    };

    for(auto button : axesButtons)
    {
        bool allAxesExists = true;
        for(auto axisId : button.first)
        {
            if(!motionContoller.axisExists(axisId))
                allAxesExists = false;
        }

        if(allAxesExists) button.second->setEnabled(true);
    }
}

void MainWindow::disableAllAxesButtons()
{
    auto axesButtons = {
        ui->movementXNegativePushButton, ui->movementXPositivePushButton,
        ui->movementYNegativePushButton, ui->movementYPositivePushButton,
        ui->movementXNegativeYNegativePushButton, ui->movementXNegativeYPositivePushButton,
        ui->movementXPositiveYNegativePushButton, ui->movementXPositiveYPositivePushButton,
        ui->movementZNegativePushButton, ui->movementZPositivePushButton,
        ui->movementANegativePushButton, ui->movementAPositivePushButton,
        ui->movementBNegativePushButton, ui->movementBPositivePushButton,
        ui->movementCNegativePushButton, ui->movementCPositivePushButton,
        ui->movementUNegativePushButton, ui->movementUPositivePushButton,
        ui->movementVNegativePushButton, ui->movementVPositivePushButton,
        ui->movementWNegativePushButton, ui->movementWPositivePushButton,
    };
    for(auto button : axesButtons)
    {
        button->setEnabled(false);
    }
}

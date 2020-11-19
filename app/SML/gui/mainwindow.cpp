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

    this->startAdapters();
}

MainWindow::~MainWindow()
{
    this->stopAdapters();
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
        }
        else
        {
            ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
            ui->statusBar->showMessage("Hardware driver is not ready");
        }
    };

    driver.registerHandler(HARDWARE_EVENT::DeviceControllerConnectionStateChanged, hardwareConnectionStateChangedHandler);
    driver.registerHandler(HARDWARE_EVENT::MotionControllerConnectionStateChanged, hardwareConnectionStateChangedHandler);
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

void MainWindow::startAdapters()
{
    try
    {
        SettingsManager s;
        QString deviceAdapterPath = s.get("ExternalTools", "DeviceAdapter").toString();
        QString motionAdapterPath = s.get("ExternalTools", "MotionAdapter").toString();

        m_adaptersLauncher.startAdapters(deviceAdapterPath, motionAdapterPath);
    }
    catch(...)
    {
        QString msg = "An error has occured during adapter starting";
        qWarning() << msg;
        QMessageBox(QMessageBox::Warning, "Warning", msg).exec();
    }

}

void MainWindow::stopAdapters()
{
    try
    {
        m_adaptersLauncher.stopAdapters();
    }
    catch(...)
    {
        qWarning() << QStringLiteral("unknown error");
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

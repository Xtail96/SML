#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_hightlighter(new GCodesSyntaxHighlighter(this))
{
    ui->setupUi(this);

    // окно на весь экран
    QMainWindow::showMaximized();

    m_shortcutsMap.push_back(std::make_tuple("A", ui->movementXNegativePushButton, SLOT(on_movementXNegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("D", ui->movementXPositivePushButton, SLOT(on_movementXPositivePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("S", ui->movementYNegativePushButton, SLOT(on_movementYNegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("W", ui->movementYPositivePushButton, SLOT(on_movementYPositivePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Z", ui->movementXNegativeYNegativePushButton, SLOT(on_movementXNegativeYNegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Q", ui->movementXNegativeYPositivePushButton, SLOT(on_movementXNegativeYPositivePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("X", ui->movementXPositiveYNegativePushButton, SLOT(on_movementXPositiveYNegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("E", ui->movementXPositiveYPositivePushButton, SLOT(on_movementXPositiveYPositivePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Down", ui->movementZNegativePushButton, SLOT(on_movementZNegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Up", ui->movementZPositivePushButton, SLOT(on_movementZPositivePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Left", ui->movementANegativePushButton, SLOT(on_movementANegativePushButton_clicked())));
    m_shortcutsMap.push_back(std::make_tuple("Right", ui->movementAPositivePushButton, SLOT(on_movementAPositivePushButton_clicked())));

    this->setupWidgets();
    this->setupConnections();

    //updateAxisesBoard();
    //updateDevicesBoard();
    //updateSensorsBoard();

    //updatePointsEditorFields();
    //updatePointsEditorButtons();

    //updateVelocityPanel();
    //updateSpindelRotationsPanel();
    //updateOptionsPanel();
    //updateDevicesPanel();
    //updateServerPanel();

    MachineTool& machineTool = MachineTool::getInstance();
    this->onMachineTool_ErrorStateChanged(machineTool.getLastError());
}

MainWindow::~MainWindow()
{
    this->resetConnections();

    // удаляем горячие клавиши
    while (m_axisesShortcuts.size() > 0)
    {
        delete m_axisesShortcuts.back();
        m_axisesShortcuts.pop_back();
    }

    delete ui;
}

void MainWindow::setupWidgets()
{
    // установка оформления statusBar
    ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    ui->statusBar->setFont(QFont("Consolas", 14));
    ui->statusBar->showMessage(tr("State: ready 0123456789"));

    this->setupSensorsDisplay();
    this->setupSensorsSettingsBoard();

    this->setupSpindelsSettingsBoard();
    this->setupSupportDevicesSettingsBoard();
    this->setupSpindelsControlPanel();

    this->setupOptionsPanel();

    // настройка контроля габаритов
    //updateEdgesControlStatus();

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

    // настройка редактора точек
    ui->pointsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pointsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pointsTableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->hideWidgets();
}

void MainWindow::setupConnections()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QObject::connect(&machineTool, SIGNAL(errorStateChanged(ERROR_CODE)), this, SLOT(onMachineTool_ErrorStateChanged(ERROR_CODE)));

    QObject::connect(&machineTool, SIGNAL(pointsUpdated()), this, SLOT(onPointsUpdated()));
    QObject::connect(&machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onMachineTool_SensorStateChanged(QString,QColor)));
    QObject::connect(&machineTool, SIGNAL(spindelStateChanged(QString,bool,size_t)), this, SLOT(onMachineTool_SpindelStateChanged(QString,bool,size_t)));
    QObject::connect(&machineTool, SIGNAL(gcodesFilePathUpdated(QString)), this, SLOT(onMachineTool_GCodesFilePathUpdated(QString)));
    QObject::connect(&machineTool, SIGNAL(gcodesFileContentUpdated(QStringList)), this, SLOT(onMachineTool_GCodesFileContentUpdated(QStringList)));

    /*QObject::connect(m_machineTool.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1Displays()));

    QObject::connect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(onU2Connected()));
    QObject::connect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(onU2Disconnected()));
    QObject::connect(m_machineTool.data(), SIGNAL(u2StateIsChanged()), this, SLOT(updateU1Displays()));

    QObject::connect(m_machineTool.data(), SIGNAL(u1Connected()), this, SLOT(updateServerPanel()));
    QObject::connect(m_machineTool.data(), SIGNAL(u1Disconnected()), this, SLOT(updateServerPanel()));
    QObject::connect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(updateServerPanel()));
    QObject::connect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(updateServerPanel()));

    QObject::connect(m_machineTool.data(), SIGNAL(machineToolErrorIsOccured(int)), this, SLOT(onMachineToolError(int)));

    QObject::connect(m_machineTool.data(), SIGNAL(gcodesUpdated()), this, SLOT(updateGCodesEditorWidget()));
    QObject::connect(m_machineTool.data(), SIGNAL(filePathUpdated()), this, SLOT(updateFilePath()));
    QObject::connect(m_machineTool.data(), SIGNAL(pointsUpdated()), this, SLOT(updatePointsEditorWidgets()));

    // задаем горячие клавиши
    for (auto i = m_shortcutsMap.begin(); i != m_shortcutsMap.end(); i++)
    {
        const char* shortcutKey = std::get<0>(*i);
        QPushButton* shortcutButton = std::get<1>(*i);
        const char* shortcutSlot = std::get<2>(*i);

        QShortcut* shortcut = new QShortcut(QKeySequence(shortcutKey), shortcutButton);
        QObject::connect(shortcut, SIGNAL(activated()), this, shortcutSlot);

        m_axisesShortcuts.push_back(shortcut);
    }

    QObject::connect(ui->edgesControlCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateEdgesControlStatus()));*/


    QList<PointsTableWidget*> pointsEditorTableWidgets = {ui->pointsTableWidget, ui->pointsTableWidget_2};
    for(auto pointsEditorTableWidget : pointsEditorTableWidgets)
    {
        QObject::connect(pointsEditorTableWidget, SIGNAL(editSignal(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
        QObject::connect(pointsEditorTableWidget, SIGNAL(eraseSignal(QModelIndexList)), this, SLOT(deletePoints(QModelIndexList)));
        QObject::connect(pointsEditorTableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
    }
    QObject::connect(ui->pointAddPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointAddPushButton_clicked()));
    QObject::connect(ui->pointDeletePushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointDeletePushButton_clicked()));
    QObject::connect(ui->pointCursorPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCursorPushButton_clicked()));
    QObject::connect(ui->pointCopyPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCopyPushButton_clicked()));

    for(size_t i = 0; i < static_cast<size_t>(ui->spindelsListWidget->count()); i++)
    {
        SpindelControlWidget* widget = qobject_cast<SpindelControlWidget*> (ui->spindelsListWidget->itemWidget(ui->spindelsListWidget->item(static_cast<int>(i))));
        QObject::connect(widget, SIGNAL(switchOn(QString,size_t)), &machineTool, SLOT(switchSpindelOn(QString,size_t)));
        QObject::connect(widget, SIGNAL(switchOff(QString)), &machineTool, SLOT(switchSpindelOff(QString)));
    }

    // настройка импорта и экспорта настроек
    QObject::connect(ui->importSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_importsettings_action_triggered()));
    QObject::connect(ui->exportSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_savesettings_action_triggered()));

    // настройка кнопок работы с файлами
    QObject::connect(ui->newFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_create_action_triggered()));
    QObject::connect(ui->openFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_open_action_triggered()));
    QObject::connect(ui->saveFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_save_action_triggered()));
    QObject::connect(ui->saveFileAsToolButton, SIGNAL(clicked(bool)), this, SLOT(on_saveas_action_triggered()));
    QObject::connect(ui->addFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_add_action_triggered()));
    QObject::connect(ui->viewToolButton, SIGNAL(clicked(bool)), this, SLOT(on_view_action_triggered()));
}

void MainWindow::resetConnections()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QObject::disconnect(&machineTool, SIGNAL(errorStateChanged(ERROR_CODE)), this, SLOT(onMachineTool_ErrorStateChanged(ERROR_CODE)));

    QObject::disconnect(&machineTool, SIGNAL(pointsUpdated()), this, SLOT(onPointsUpdated()));
    QObject::disconnect(&machineTool, SIGNAL(sensorStateChanged(QString,QColor)), this, SLOT(onMachineTool_SensorStateChanged(QString,QColor)));
    QObject::disconnect(&machineTool, SIGNAL(spindelStateChanged(QString,bool,size_t)), this, SLOT(onMachineTool_SpindelStateChanged(QString,bool,size_t)));
    QObject::disconnect(&machineTool, SIGNAL(gcodesFilePathUpdated(QString)), this, SLOT(onMachineTool_GCodesFilePathUpdated(QString)));
    QObject::disconnect(&machineTool, SIGNAL(gcodesFileContentUpdated(QStringList)), this, SLOT(onMachineTool_GCodesFileContentUpdated(QStringList)));

    /*QObject::disconnect(m_machineTool.data(), SIGNAL(u1StateIsChanged()), this, SLOT(updateU1Displays()));

    QObject::disconnect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(onU2Connected()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(onU2Disconnected()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(u2StateIsChanged()), this, SLOT(updateU1Displays()));

    QObject::disconnect(m_machineTool.data(), SIGNAL(u1Connected()), this, SLOT(updateServerPanel()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(u1Disconnected()), this, SLOT(updateServerPanel()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(u2Connected()), this, SLOT(updateServerPanel()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(u2Disconnected()), this, SLOT(updateServerPanel()));

    QObject::disconnect(m_machineTool.data(), SIGNAL(machineToolErrorIsOccured(int)), this, SLOT(onMachineToolError(int)));

    QObject::disconnect(m_machineTool.data(), SIGNAL(gcodesUpdated()), this, SLOT(updateGCodesEditorWidget()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(filePathUpdated()), this, SLOT(updateFilePath()));
    QObject::disconnect(m_machineTool.data(), SIGNAL(pointsUpdated()), this, SLOT(updatePointsEditorWidgets()));

    QObject::disconnect(ui->edgesControlCheckBox, SIGNAL(clicked(bool)), this, SLOT(updateEdgesControlStatus()));*/


    QList<PointsTableWidget*> pointsEditorTableWidgets = {ui->pointsTableWidget, ui->pointsTableWidget_2};
    for(auto pointsEditorTableWidget : pointsEditorTableWidgets)
    {
        QObject::disconnect(pointsEditorTableWidget, SIGNAL(editSignal(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
        QObject::disconnect(pointsEditorTableWidget, SIGNAL(eraseSignal(QModelIndexList)), this, SLOT(deletePoints(QModelIndexList)));
        QObject::disconnect(pointsEditorTableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(editPoint(QModelIndex)));
    }
    QObject::disconnect(ui->pointAddPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointAddPushButton_clicked()));
    QObject::disconnect(ui->pointDeletePushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointDeletePushButton_clicked()));
    QObject::disconnect(ui->pointCursorPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCursorPushButton_clicked()));
    QObject::disconnect(ui->pointCopyPushButton_2, SIGNAL(clicked(bool)), this, SLOT(on_pointCopyPushButton_clicked()));

    for(size_t i = 0; i < static_cast<size_t>(ui->spindelsListWidget->count()); i++)
    {
        SpindelControlWidget* widget = qobject_cast<SpindelControlWidget*> (ui->spindelsListWidget->itemWidget(ui->spindelsListWidget->item(static_cast<int>(i))));
        QObject::disconnect(widget, SIGNAL(switchOn(QString,size_t)), &machineTool, SLOT(switchSpindelOn(QString,size_t)));
        QObject::disconnect(widget, SIGNAL(switchOff(QString)), &machineTool, SLOT(switchSpindelOff(QString)));
    }

    // настройка импорта и экспорта настроек
    QObject::disconnect(ui->importSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_importsettings_action_triggered()));
    QObject::disconnect(ui->exportSettingsPushButton, SIGNAL(clicked(bool)), this, SLOT(on_savesettings_action_triggered()));


    // настройка кнопок работы с файлами
    QObject::disconnect(ui->newFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_create_action_triggered()));
    QObject::disconnect(ui->openFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_open_action_triggered()));
    QObject::disconnect(ui->saveFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_save_action_triggered()));
    QObject::disconnect(ui->saveFileAsToolButton, SIGNAL(clicked(bool)), this, SLOT(on_saveas_action_triggered()));
    QObject::disconnect(ui->addFileToolButton, SIGNAL(clicked(bool)), this, SLOT(on_add_action_triggered()));
    QObject::disconnect(ui->viewToolButton, SIGNAL(clicked(bool)), this, SLOT(on_view_action_triggered()));
}

void MainWindow::setupSensorsDisplay()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QStringList names = machineTool.getRepository()->getAllSensorsUids();

    for(auto name : names)
    {
        QMap<QString, QString> parameters = machineTool.getRepository()->getSensorSettings(name);
        ui->sensorsDisplayWidget->addSensor(parameters["Uid"], parameters["Label"], QColor(SmlColors::white()));
    }
}

void MainWindow::onMachineTool_SensorStateChanged(QString name, QColor color)
{
    ui->sensorsDisplayWidget->updateSensorState(name, color);
}

void MainWindow::onMachineTool_SpindelStateChanged(QString index, bool enable, size_t rotations)
{
    bool ok = false;

    size_t spindelIndex = index.toUInt(&ok);

    if(ok)
    {
        SpindelControlWidget* widget = qobject_cast<SpindelControlWidget*> (ui->spindelsListWidget->itemWidget(ui->spindelsListWidget->item(static_cast<int>(spindelIndex))));
        widget->updateControls(enable, rotations);
    }
}

void MainWindow::setupSensorsSettingsBoard()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QStringList sensorsSettings = machineTool.getRepository()->getAllSensorsSettings();

    QStringList labels;
    QList< QPair<int, int> > positions;
    QList<QTableWidgetItem*> items;

    // rows
    for(int i = 0; i < sensorsSettings.size(); i++)
    {
        QStringList sensorSettings = sensorsSettings.at(i).split(";");
        // columns
        for(int j = 0; j < sensorSettings.size(); j++)
        {
            QStringList pair = sensorSettings[j].split(":");
            //qDebug() << pair;
            if(pair.size() == 2)
            {
                if(!labels.contains(pair.at(0)))
                {
                    labels.push_back(pair.at(0));
                }

                QTableWidgetItem* item = new QTableWidgetItem(pair.at(1));
                items.push_back(item);
                positions.push_back(QPair<int, int>(i, j));
            }
        }
    }

    ui->sensorsSettingsTableWidget->setColumnCount(labels.size());
    ui->sensorsSettingsTableWidget->setHorizontalHeaderLabels(labels);

    ui->sensorsSettingsTableWidget->setRowCount(sensorsSettings.size());
    for(int i = 0; i < items.size(); i++)
    {
        ui->sensorsSettingsTableWidget->setItem(positions[i].first, positions[i].second, items[i]);
    }
}

void MainWindow::setupSpindelsControlPanel()
{
    MachineTool& machineTool = MachineTool::getInstance();

    ui->spindelsListWidget->clear();
    auto spindels = machineTool.getRepository()->getSpindels();
    for(auto spindel : spindels)
    {
        SpindelControlWidget* widget = new SpindelControlWidget(spindel->getLabel(),
                                                                spindel->getSettingsUId(),
                                                                spindel->getUid(),
                                                                spindel->getUpperBound(),
                                                                spindel->getLowerBound(),
                                                                spindel->getCurrentRotations(),
                                                                spindel->isEnable(),
                                                                ui->spindelsListWidget);

        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(widget->minimumSizeHint());

        ui->spindelsListWidget->addItem(item);
        ui->spindelsListWidget->setItemWidget(item, widget);
    }
}

void MainWindow::setupSpindelsSettingsBoard()
{
    MachineTool& machineTool = MachineTool::getInstance();
    QStringList spindelsSettings = machineTool.getRepository()->getAllSpindelsSettings();

    QStringList labels;
    QList< QPair<int, int> > positions;
    QList<QTableWidgetItem*> items;

    // rows
    for(int i = 0; i < spindelsSettings.size(); i++)
    {
        QStringList spindelSettings = spindelsSettings.at(i).split(";");
        // columns
        for(int j = 0; j < spindelSettings.size(); j++)
        {
            QStringList pair = spindelSettings[j].split(":");
            //qDebug() << pair;
            if(pair.size() == 2)
            {
                if(!labels.contains(pair.at(0)))
                {
                    labels.push_back(pair.at(0));
                }

                QTableWidgetItem* item = new QTableWidgetItem(pair.at(1));
                items.push_back(item);
                positions.push_back(QPair<int, int>(i, j));
            }
        }
    }

    ui->spindelsSettingsTableWidget->setColumnCount(labels.size());
    ui->spindelsSettingsTableWidget->setHorizontalHeaderLabels(labels);

    ui->spindelsSettingsTableWidget->setRowCount(spindelsSettings.size());
    for(int i = 0; i < items.size(); i++)
    {
        ui->spindelsSettingsTableWidget->setItem(positions[i].first, positions[i].second, items[i]);
    }
}

void MainWindow::setupSupportDevicesSettingsBoard()
{
    MachineTool& machineTool = MachineTool::getInstance();
    QStringList supportDevicesSettings = machineTool.getRepository()->getAllSupportDeviceSettings();

    QStringList labels;
    QList< QPair<int, int> > positions;
    QList<QTableWidgetItem*> items;

    // rows
    for(int i = 0; i < supportDevicesSettings.size(); i++)
    {
        QStringList supportDeviceSettings = supportDevicesSettings.at(i).split(";");
        // columns
        for(int j = 0; j < supportDeviceSettings.size(); j++)
        {
            QStringList pair = supportDeviceSettings[j].split(":");
            //qDebug() << pair;
            if(pair.size() == 2)
            {
                if(!labels.contains(pair.at(0)))
                {
                    labels.push_back(pair.at(0));
                }

                QTableWidgetItem* item = new QTableWidgetItem(pair.at(1));
                items.push_back(item);
                positions.push_back(QPair<int, int>(i, j));
            }
        }
    }

    ui->supportDevicesSettingsTableWidget->setColumnCount(labels.size());
    ui->supportDevicesSettingsTableWidget->setHorizontalHeaderLabels(labels);

    ui->supportDevicesSettingsTableWidget->setRowCount(supportDevicesSettings.size());
    for(int i = 0; i < items.size(); i++)
    {
        ui->supportDevicesSettingsTableWidget->setItem(positions[i].first, positions[i].second, items[i]);
    }
}

void MainWindow::setupAxisesBoard()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QStringList axisesSettings = machineTool.getRepository()->getAxisesSettings();
    ui->axisesSettingsListWidget->addItems(axisesSettings);
}


void MainWindow::updateCoordinatesDisplays()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QList<Point> machineToolCoordinates = machineTool.getRepository()->getMachineToolCoordinates();

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

void MainWindow::onMachineTool_GCodesFileContentUpdated(QStringList data)
{
    ui->gcodesEditorPlainTextEdit->setPlainText(data.join('\n'));
}

void MainWindow::onMachineTool_GCodesFilePathUpdated(QString path)
{
    ui->filePathLineEdit->setText(path);
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

void MainWindow::setupOptionsPanel()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QStringList optionsNames = machineTool.getRepository()->getOptionsLabels();
    ui->optionsListWidget->addItems(optionsNames);
}

void MainWindow::hideWidgets()
{
    ui->smlEditorTreeWidget->setEnabled(false);
    ui->commandsToolsListWidget->setEnabled(false);
}

void MainWindow::onMachineTool_ErrorStateChanged(ERROR_CODE errorCode)
{
    MachineTool& machineTool = MachineTool::getInstance();

    ui->serverPortLcdNumber->display(machineTool.getAdapterServerPort());
    ui->sensorsBufferSizeLcdNumber->display(machineTool.getRepository()->getSensorsBufferSize());
    ui->devicesBufferSizeLcdNumber->display(machineTool.getRepository()->getDevicesBufferSize());
    ui->currentConnectionsListWidget->clear();
    ui->currentConnectionsListWidget->addItems(machineTool.getConnectedAdapters());

    bool enableWidgets = false;
    if(errorCode == OK)
    {
        enableWidgets = true;
        ui->statusBar->setStyleSheet("background-color: #333; color: #33bb33");
    }
    else
    {
        ui->statusBar->setStyleSheet("background-color: #333; color: #b22222");
    }

    QString errorString = QStringLiteral("Error code #") + QString::number(errorCode);
    ui->statusBar->showMessage(errorString);

    ui->optionsListWidget->setEnabled(enableWidgets);
    ui->spindelsListWidget->setEnabled(enableWidgets);

    ui->currentCoordinatesListWidget->setEnabled(enableWidgets);
    ui->baseCoordinatesListWidget->setEnabled(enableWidgets);
    ui->parkCoordinatesListWidget->setEnabled(enableWidgets);
    ui->edgesControlCheckBox->setEnabled(enableWidgets);

    ui->movementXNegativePushButton->setEnabled(enableWidgets);
    ui->movementXPositivePushButton->setEnabled(enableWidgets);
    ui->movementXNegativeYNegativePushButton->setEnabled(enableWidgets);
    ui->movementXNegativeYPositivePushButton->setEnabled(enableWidgets);
    ui->movementXPositiveYNegativePushButton->setEnabled(enableWidgets);
    ui->movementXPositiveYPositivePushButton->setEnabled(enableWidgets);
    ui->movementYNegativePushButton->setEnabled(enableWidgets);
    ui->movementYPositivePushButton->setEnabled(enableWidgets);
    ui->movementZNegativePushButton->setEnabled(enableWidgets);
    ui->movementZPositivePushButton->setEnabled(enableWidgets);
    ui->movementANegativePushButton->setEnabled(enableWidgets);
    ui->movementAPositivePushButton->setEnabled(enableWidgets);
    ui->movementBNegativePushButton->setEnabled(enableWidgets);
    ui->movementBPositivePushButton->setEnabled(enableWidgets);
    ui->movementCNegativePushButton->setEnabled(enableWidgets);
    ui->movementCPositivePushButton->setEnabled(enableWidgets);
    ui->movementDNegativePushButton->setEnabled(enableWidgets);
    ui->movementDPositivePushButton->setEnabled(enableWidgets);

    for(auto shortcut : m_axisesShortcuts)
    {
        shortcut->setEnabled(enableWidgets);
    }

    ui->discreteRadioButton_1->setEnabled(enableWidgets);
    ui->discreteRadioButton_2->setEnabled(enableWidgets);
    ui->discreteRadioButton_3->setEnabled(enableWidgets);
    ui->discreteRadioButton_4->setEnabled(enableWidgets);
    ui->discreteRadioButton_5->setEnabled(enableWidgets);

    ui->feedrateScrollBar->setEnabled(enableWidgets);
    ui->feedrateLcdNumber->setEnabled(enableWidgets);

    ui->toBasePushButton->setEnabled(enableWidgets);
    ui->toZeroPushButton->setEnabled(enableWidgets);
    ui->toParkPushButton->setEnabled(enableWidgets);
    ui->zeroPushButton->setEnabled(enableWidgets);
    ui->zeroSensorPushButton->setEnabled(enableWidgets);
    ui->parkPushButton->setEnabled(enableWidgets);

    ui->runCommandLinkButton->setEnabled(enableWidgets);
    ui->stopCommandLinkButton->setEnabled(enableWidgets);
}

void MainWindow::disableMovementButtonsShortcutsAutoRepeat()
{
    //setMovementButtonsShortcutsAutoRepeat(false);
}

void MainWindow::enableMovementButtonsShortcutsAutoRepeat()
{
    //setMovementButtonsShortcutsAutoRepeat(true);
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

    //disableMovementButtonsShortcutsAutoRepeat();
    //setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_2_clicked()
{
    //MachineTool::Instance().setMovementStep(0.1);

    //disableMovementButtonsShortcutsAutoRepeat();
    //setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_3_clicked()
{
    //MachineTool::Instance().setMovementStep(1);

    //disableMovementButtonsShortcutsAutoRepeat();
    //setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_4_clicked()
{
    //MachineTool::Instance().setMovementStep(10);

    //disableMovementButtonsShortcutsAutoRepeat();
    //setMovementButtonsRepeatAutoRepeat(false);
}

void MainWindow::on_discreteRadioButton_5_clicked()
{
    //MachineTool::Instance().setMovementStep(0);

    //enableMovementButtonsShortcutsAutoRepeat();
    //setMovementButtonsRepeatAutoRepeat(true);
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
    MachineTool& machineTool = MachineTool::getInstance();
    machineTool.getRepository()->setVelocity(value);
    ui->feedrateLcdNumber->display(QString::number(machineTool.getRepository()->getVelocity()));
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
        QModelIndexList selectedRowsIndexes = PointsTableWidget::getRowsIndexes(selectedItemsIndexes);
        deletePoints(selectedRowsIndexes);
    }
}

void MainWindow::on_pointCursorPushButton_clicked()
{
    PointsTableWidget* currentTableWidget;
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
    MachineTool& machineTool = MachineTool::getInstance();

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
        QModelIndexList selectedRowsIndexes = PointsTableWidget::getRowsIndexes(selectedItemsIndexes);

        for(auto row : selectedRowsIndexes)
        {
            QStringList pointsArguments = machineTool.getRepository()->getPoint(static_cast<unsigned int>(row.row()));
            machineTool.getRepository()->addPoint(pointsArguments);
        }
    }
    else
    {
        return;
    }
}

void MainWindow::onMachineTool_EdgesControlStatusChanged(bool state)
{
    ui->edgesControlCheckBox->setChecked(state);
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
    MachineTool& machineTool = MachineTool::getInstance();
    AddPointDialog(*(machineTool.getRepository()), this).exec();
}

void MainWindow::editPoint(QModelIndex index)
{
    MachineTool& machineTool = MachineTool::getInstance();

    try
    {
        AddPointDialog(*(machineTool.getRepository()), static_cast<unsigned int>(index.row()), this).exec();
    }
    catch(std::out_of_range e)
    {
        QMessageBox(QMessageBox::Warning, "Ошибка", e.what()).exec();
    }
}

void MainWindow::deletePoints(QModelIndexList indexes)
{
    MachineTool& machineTool = MachineTool::getInstance();

    for(int i = indexes.size() - 1; i >= 0; i--)
    {
        machineTool.getRepository()->deletePoint(static_cast<unsigned int>(indexes[i].row()));
    }
}

void MainWindow::onPointsUpdated()
{
    MachineTool& machineTool = MachineTool::getInstance();

    QList<QStringList> points = machineTool.getRepository()->getPoints();
    QList<PointsTableWidget*> fields = { ui->pointsTableWidget, ui->pointsTableWidget_2 };
    QStringList axisesLabels = machineTool.getRepository()->getAxisesNames();

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

void MainWindow::on_open_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->openSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            machineTool.getRepository()->openGCodesFile();
        }
    }
}

void MainWindow::on_gcodesEditorPlainTextEdit_textChanged()
{
    QString text = ui->gcodesEditorPlainTextEdit->toPlainText();
}

void MainWindow::on_importsettings_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    machineTool.getRepository()->importSettings();
}

void MainWindow::on_savesettings_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    machineTool.getRepository()->exportSettings();
}

void MainWindow::on_add_action_triggered()
{
    /*if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->addSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            m_machineTool->addGCodesFile(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }*/
}

void MainWindow::on_create_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->newSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            machineTool.getRepository()->newGCodesFile();
        }
    }
}

void MainWindow::on_save_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->saveSMLFile();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            machineTool.getRepository()->saveGCodesFile(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_saveas_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    if(ui->smlEditorTab->isVisible())
    {
        //mainWindowController->saveSMLFileAs();
    }
    else
    {
        if(ui->gcodesEditorTab->isVisible())
        {
            machineTool.getRepository()->saveGCodesFileAs(ui->gcodesEditorPlainTextEdit->toPlainText());
        }
    }
}

void MainWindow::on_runCommandLinkButton_clicked()
{
    /*QString content = ui->gcodesEditorPlainTextEdit->toPlainText();
    m_machineTool->setGCodes(content);
    m_machineTool->parseGCodes();*/
}

void MainWindow::on_view_action_triggered()
{
    MachineTool& machineTool = MachineTool::getInstance();

    machineTool.getRepository()->setGCodes(ui->gcodesEditorPlainTextEdit->toPlainText());
    CandleVisualizerDialog(machineTool.getRepository()->getGCodesProgram(), this).exec();
}

void MainWindow::on_consoleOpenPushButton_clicked()
{
    MachineTool& machineTool = MachineTool::getInstance();

    SMLConsoleDialog(machineTool, this).exec();
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
    MachineTool& machineTool = MachineTool::getInstance();

    machineTool.getRepository()->setSoftLimitsMode(ui->edgesControlCheckBox->isChecked());
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

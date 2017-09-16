#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <set>
#include <tuple>
#include <vector>
#include <deque>

#include <QMainWindow>
#include <QTimer>
#include <QShortcut>
#include <QKeySequence>
#include <QList>
#include <QMessageBox>
#include <QTreeWidget>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTableWidgetItem>
#include <QListWidget>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "models/machinetool/machinetool.h"
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "points/addpointdialog.h"
#include "points/toselectionpointdialog.h"
#include "models/machinetool/commandsinterpreter/commandsinterpreter.h"

#include "commands/commanddialog.h"
#include "commands/linedialog.h"
#include "commands/ttlinedialog.h"
#include "commands/arcdialog.h"
#include "commands/arc2dialog.h"
#include "commands/ttzarcdialog.h"
#include "commands/tttarcdialog.h"
#include "commands/labeldialog.h"
#include "commands/cycledialog.h"
#include "commands/procdialog.h"
#include "commands/ondialog.h"
#include "commands/offdialog.h"
#include "commands/rotatedialog.h"
#include "commands/gotodialog.h"
#include "commands/callprocdialog.h"
#include "commands/scaledialog.h"
#include "commands/velocitydialog.h"
#include "commands/pausedialog.h"
#include "commands/stopdialog.h"
#include "commands/commentdialog.h"
#include "commands/splinedialog.h"
#include "commands/ttttsplinedialog.h"
#include "programvisualizewindow.h"

#include "models/machinetool/commandsmanager/commands/commands.h"

#include "gcodessyntaxhighlighter.h"
#include "models/machinetool/settingsmanager/settingsmanager.h"

#include "models/controllerconnector/usbdevicesmanager/usbdevice/usbdevice.h"
#include "models/controllerconnector/debugmodule/debugmodule.h"
#include "models/controllerconnector/usbdevicesmanager/usbdevicesmanager.h"

#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevicemanager.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/usbxpressdevice.h"
#include "models/controllerconnector/usbxpressdevicesmanager/usbxpressdevice/silabsu1.h"

#include "gui/options/kabriolwindow.h"
#include "gui/options/toollengthsensorwindow.h"
#include "gui/options/lubricationsystemwindow.h"

#include "dependencies.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QTimer *timer;

    std::vector<QShortcut*> shortcuts;
    std::vector<QShortcut*> editorShortcuts;

    GCodesSyntaxHighlighter* hightlighter;

    void setupMachineTool();

    /// Методя для заполнения таблиц настроек
    QTableWidgetItem* fillSensorsSettingsTable(const std::vector< std::shared_ptr<Sensor> > &sensors, int parametrIndex, int sensorIndex);
    QTableWidgetItem* fillDevicesSettingsTable(const std::vector< std::shared_ptr<Device> > &devices, int parametrIndex, int deviceIndex);
    QTableWidgetItem* fillAxisesSettingsTable(const std::vector<std::shared_ptr<Axis> > &axises, int axisIndex, int parametrIndex);


    void disableMovementButtonsShortcuts();
    void enableMovementButtonsShortcuts();

    void setMovementButtonsShortcutsState(bool state);
    void setMovementButtonsRepeatState(bool state);

    void showMachineToolConnected();
    void showMachineToolDisconnected();

    void setSelectedCommandVectorNumber(unsigned int& current_row);


    MachineTool* machineTool;
    //UsbDevicesManager* u1Connector;

#ifdef Q_OS_WIN
    UsbXpressDeviceManager* u1Manager;
#endif

protected:

private slots:
    /// Слоты для настройки виджетов
    void setupWidgets();

    /// Слоты для настройки горячих клавиш
    void setupAxisesShortcuts();

    /// Слоты для настройки Status Bar
    void setupStatusBar();

    /// Слоты для настройки панели координат
    void setupCoordinatesPanel();
    void setupEdgesControl();

    /// Слоты для настройки редактора команд
    void setupTreeWidget();
    void setupGCodesSyntaxHighlighter();

    /// Слоты для настройки элементов менеджера файлов
    void setupEditorFileActionsPushButtons();

    /// Слоты, для настройки редактора точек
    void setupPointsTableWidgets();
    void setupPointsPushButtons();

    /// Слоты для настройки таймера обновления панелей
    void setupTimer();

    /// Слоты для обновления панелей
    void update();

    /// Слот для обновления панели координат
    void updateCoordinatesPanel();

    /// Слот для обновления панели датчиков
    void updateSensorsPanel();

    /// Слот для обновления панели устройств
    void updateDevicesPanel();

    /// Слот для обновления панели заряда батареи
    void updateBatteryStatusPanel();

    /// Слот для обновления панели посылки со станка
    void updateMachineToolStatusPanel();

    /// Слот для обновления настроек
    void updateSettingsFields();

    /// Слот для обновления таблицы настроек датчиков
    void updateSensorsSettingsField();

    /// Слот для обновления таблицы настроек устройств
    void updateDevicesSettingsField();

    /// Слот для обновления таблицы настроек осей
    void updateAxisSettingsField();

    /// Слот для обновления таблиц редактора точек
    void updatePointsEditorTableWidgets();

    /// Слот для обновления дерева SML-команд
    void updateSMLCommandsTreeWidget();

    /// Слот для обновления статуса баировки станка
    void updateBaseStatus();

    // to do исправить слот
    void updateEdgesControlStatus();


    /// Слоты для обработки сигналов виджета дерева SML-команд
    void commandsCopySlot();
    void commandsCutSlot();
    void commandsPasteSlot();
    void commandsUndoSlot();
    void deleteSelectedCommands();


    /// Слоты для прямого взаимодействия с элеменами интерфейса
    void on_discreteRadioButton_1_clicked();
    void on_discreteRadioButton_2_clicked();
    void on_discreteRadioButton_3_clicked();
    void on_discreteRadioButton_4_clicked();
    void on_discreteRadioButton_5_clicked();

    void on_movementXPositivePushButton_clicked();
    void on_movementXNegativePushButton_clicked();
    void on_movementYPositivePushButton_clicked();
    void on_movementYNegativePushButton_clicked();

    void on_movementXPositiveYPositivePushButton_clicked();
    void on_movementXPositiveYNegativePushButton_clicked();
    void on_movementXNegativeYPositivePushButton_clicked();
    void on_movementXNegativeYNegativePushButton_clicked();

    void on_movementZNegativePushButton_clicked();
    void on_movementZPositivePushButton_clicked();

    void on_movementAPositivePushButton_clicked();
    void on_movementANegativePushButton_clicked();

    void on_feedrateScrollBar_valueChanged(int value);

    void on_rotationsScrollBar_valueChanged(int value);

    void on_exit_action_triggered();

    void on_pointsAmountPushButton_clicked();
    void on_parkPushButton_clicked();
    void on_pointAddPushButton_clicked();
    void on_pointDeletePushButton_clicked();
    void on_zeroPushButton_clicked();
    void on_pointCursorPushButton_clicked();
    void on_pointEditPushButton_clicked();
    void on_pointCopyPushButton_clicked();
    void on_toBasePushButton_clicked();
    void on_open_action_triggered();
    void on_gcodesEditorTextEdit_textChanged();
    void on_importsettings_action_triggered();
    void on_savesettings_action_triggered();
    void on_startDegbugCommandLinkButton_clicked();
    void on_finishDebugCommandLinkButton_clicked();
    void on_devicesTableWidget_clicked(const QModelIndex &index);
    void on_commandsToolsListWidget_itemClicked(QListWidgetItem *item);
    void on_viewPushButton_clicked();
    void on_smlEditorTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_kabriolWidgetPushButton_clicked();
    void on_toolLengthSensorPushButton_clicked();
    void on_lubricationSystemPushButton_clicked();
};


#endif // MAINWINDOW_H

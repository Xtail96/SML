#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

/// Подключение диалогов редактора точек
#include "points/addpointdialog.h"
#include "points/toselectionpointdialog.h"

/// Подключение диалогов команд
/*#include "commands/linedialog.h"
#include "commands/smlttlinedialog.h"
#include "commands/arcdialog.h"
#include "commands/arc2dialog.h"
#include "commands/ttzarcdialog.h"
#include "commands/smltttarcdialog.h"
#include "commands/labeldialog.h"
#include "commands/cycledialog.h"
#include "commands/procdialog.h"
#include "commands/smlswitchondialog.h"
#include "commands/smlswitchoffdialog.h"
#include "commands/rotatedialog.h"
#include "commands/gotodialog.h"
#include "commands/callprocdialog.h"
#include "commands/scaledialog.h"
#include "commands/velocitydialog.h"
#include "commands/smlpausedialog.h"
#include "commands/stopdialog.h"
#include "commands/smlcommentdialog.h"
#include "commands/splinedialog.h"
#include "commands/ttttsplinedialog.h"
#include "commands/smlvariabledialog.h"

/// Подключение окна визуализации УП
#include "programvisualizewindow.h"*/

/// Подключение журнала
#include "logdialog.h"

/// Подключение подсветки синтаксиса G-кодов
#include "gcodessyntaxhighlighter.h"

/// Подключение менеджера настроек
#include "models/settingsmanager/settingsmanager.h"

/// Подключение диалогов опций
/*#include "gui/options/kabriolwindow.h"
#include "gui/options/toollengthsensorwindow.h"
#include "gui/options/lubricationsystemwindow.h"*/

/// Подключение файла с библиотечными зависимостями
//#include "dependencies.h"

#include "presenters/mainwindowpresenter/mainwindowpresenter.h"

#include "gcodeswebviewdialog.h"
#include "views/candlevisualizerdialog.h"
#include "smlconsoledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    /// Контроллер главного окна
    MainWindowPresenter* m_mainWindowPresenter;
    void setupMainWindowPresenter();

    /// Горячие клавиши кнопок для перемещения по осям станка
    std::vector<QShortcut*> m_axisesShortcuts;

    /// Подсветки синтаксиса в редакторе G-кодов
    GCodesSyntaxHighlighter* m_hightlighter;


    /// Методы для настройки работы горячих клавиш движения по осям станка
    void disableMovementButtonsShortcutsAutoRepeat();
    void enableMovementButtonsShortcutsAutoRepeat();
    void setMovementButtonsShortcutsAutoRepeat(bool state);
    void setMovementButtonsRepeatAutoRepeat(bool state);

private slots:
    /// Слоты для настройки виджетов
    void setupWidgets();

    /// Слоты для обновления дисплеев
    void updateDisplays();

    /// Слот для обновления дисплея координат
    void updateCoordinatesDisplays();
    void showCoordinates(QListWidget* display, Point coordinates);

    /// Слот для обновления дисплея датчиков
    void updateSensorsDisplay();

    /// Слот для обновления дисплея заряда батареи
    void updateBatteryStatusDisplay();

    /// Слот для обновления настроек
    void updateSettingsBoards();

    /// Слот для обновления "доски" настроек датчиков
    void updateSensorsBoard();

    /// Слот для обновления "доски" настроек устройств
    void updateDevicesBoard();

    /// Слот для обновления "доски" настроек осей
    void updateAxisesBoard();

    /// Слот для обновления таблиц редактора точек
    void updatePointsEditorWidgets();
    void updatePointsEditorFields();
    void updatePointsEditorButtons();

    /// Слот для обновления дерева SML-команд
    void updateGCodesEditorWidget();
    void updateFilePath();

    /// Слот для обновления статуса баировки станка
    void updateBaseStatus();

    /// Слот для обновления панели устройств
    void updateDevicesPanel();
    void updateDevicesLeds();

    /// Слот для обновления скорости
    void updateVelocityPanel();

    /// Слот для обновления оборотов шпинделя
    void updateSpindelRotationsPanel();

    /// Слот для обновления панели опций
    void updateOptionsPanel();

    void hideWidgets();

    // to do исправить слот
    void updateEdgesControlStatus();

    void addPoint();
    void editPoint(QModelIndex index);
    void deletePoints(QModelIndexList indexes);


    /// Слоты для обработки сигналов виджета дерева SML-команд
    //void commandsCopySlot();
    //void commandsCutSlot();
    //void commandsPasteSlot();
    //void commandsUndoSlot();
    //void deleteSelectedCommands(QModelIndexList indexes);

    /// Слоты для отображения поддержки/отсутсвия связи со станком
    void onMachineToolConnected();
    void onMachineToolDisconnected(QString message);

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
    void on_pointAddPushButton_clicked();
    void on_pointDeletePushButton_clicked();
    void on_pointCursorPushButton_clicked();
    void on_pointEditPushButton_clicked();
    void on_pointCopyPushButton_clicked();
    void on_open_action_triggered();
    void on_gcodesEditorPlainTextEdit_textChanged();
    void on_importsettings_action_triggered();
    void on_savesettings_action_triggered();
    //void on_smlEditorTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    //void on_commandsToolsListWidget_clicked(const QModelIndex &index);
    void on_devicesButtonsListWidget_clicked(const QModelIndex &index);
    void on_add_action_triggered();
    void on_create_action_triggered();
    void on_save_action_triggered();
    void on_saveas_action_triggered();
    void on_connectCommandLinkButton_clicked();
    void on_runCommandLinkButton_clicked();
    void on_view_action_triggered();
    void on_consoleOpenPushButton_clicked();
    void on_disconnectCommandLinkButton_clicked();
};


#endif // MAINWINDOW_H

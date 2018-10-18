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
#include "gui/addpointdialog.h"
#include "gui/toselectionpointdialog.h"

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
#include "commands/smlvariabledialog.h"*/

/// Подключение подсветки синтаксиса G-кодов
#include "gcodessyntaxhighlighter.h"

/// Подключение диалогов опций
/*#include "gui/options/kabriolwindow.h"
#include "gui/options/toollengthsensorwindow.h"
#include "gui/options/lubricationsystemwindow.h"*/

#include "models/machinetool.h"

#include "gui/candlevisualizerdialog.h"
#include "gui/smlconsoledialog.h"
#include "gui/widgets/spindelcontrolwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

    /// Горячие клавиши кнопок для перемещения по осям станка
    QList< std::tuple<const char*, QPushButton*, const char*> > m_shortcutsMap;
    QList<QShortcut*> m_axisesShortcuts;

    /// Подсветки синтаксиса в редакторе G-кодов
    QScopedPointer<GCodesSyntaxHighlighter> m_hightlighter;

    /// Проводит начальную настройку виджетов
    void setupWidgets();

    /// Проводит инициализацию дисплея датчиков
    void setupSensorsDisplay();

    /// Проводит инициализацию таблицы настроек датчиков
    void setupSensorsSettingsBoard();

    /// Проводит инициализацию панели шпинделей
    void setupSpindelsControlPanel();

    /// Настраивает панель опций
    void setupOptionsPanel();

    /// Проводит инициализацию таблицы настроек устройств
    void setupDevicesBoard();

    /// Проводит инициализацию списка настроек осей
    void setupAxisesBoard();

    /// Блокирует и скрывает виджеты, которые не нужны в данной сборке, но нужны в принципе
    void hideWidgets();

    /// Подключает необходимые слоты к полям и сигналам
    void setupConnections();

    /// Отключает слоты от полей и сигналов
    void resetConnections();

    /// Методы для настройки работы горячих клавиш движения по осям станка
    void disableMovementButtonsShortcutsAutoRepeat();
    void enableMovementButtonsShortcutsAutoRepeat();
    void setMovementButtonsShortcutsAutoRepeat(bool state);
    void setMovementButtonsRepeatAutoRepeat(bool state);

private slots:
    /// Слоты для отображения поддержки/отсутсвия связи со станком
    void onMachineTool_U1Connected();
    void onMachineTool_U1Disconnected();

    void onMachineTool_U2Connected();
    void onMachineTool_U2Disconnected();

    /// Слоты для обработки ошибок станка
    void onMachineTool_ErrorOccured(int errorCode);

    /// слот для обновления дисплея датчиков
    void onMachineTool_SensorStateChanged(QString name, QColor color);

    void onMachineTool_SpindelStateChanged(QString index, bool enable, size_t rotations);

    /// Слот для обновления дисплея координат
    void updateCoordinatesDisplays();
    void showCoordinates(QListWidget* display, Point coordinates);

    /// Слот для обновления дисплея заряда батареи
    void updateBatteryStatusDisplay();

    void onMachineTool_GCodesFileContentUpdated(QString data);
    void onMachineTool_GCodesFilePathUpdated(QString path);

    // слот пока не используется
    void onMachineTool_EdgesControlStatusChanged(bool state);

    void addPoint();
    void editPoint(QModelIndex index);
    void deletePoints(QModelIndexList indexes);
    void onPointsUpdated();

    /// Слоты для обработки сигналов виджета дерева SML-команд
    //void commandsCopySlot();
    //void commandsCutSlot();
    //void commandsPasteSlot();
    //void commandsUndoSlot();
    //void deleteSelectedCommands(QModelIndexList indexes);

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
    //void on_devicesButtonsListWidget_clicked(const QModelIndex &index);
    void on_add_action_triggered();
    void on_create_action_triggered();
    void on_save_action_triggered();
    void on_saveas_action_triggered();
    void on_runCommandLinkButton_clicked();
    void on_view_action_triggered();
    void on_consoleOpenPushButton_clicked();
    void on_edgesControlCheckBox_clicked();
    void on_syntaxHighlightingCheckBox_clicked();
};


#endif // MAINWINDOW_H

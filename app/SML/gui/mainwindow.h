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

/// Подключение подсветки синтаксиса G-кодов
#include "./gui/utils/gcodes_syntax_highlighter.h"
#include "./hardware/hardware_driver.h"
#include "./gui/widgets/spindel_control_widget.h"
#include "../gui/widgets/axis_push_button.h"

#include "./services/gcodes_view_interactor.h"
#include "./services/adapters_launcher.h"
#include "./utils/utils.h"

const int INF_MOVE = 1000;

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

    QList<QMetaObject::Connection> m_slotsInfo;

    /// Подсветки синтаксиса в редакторе G-кодов
    QScopedPointer<GCodesSyntaxHighlighter> m_hightlighter;

    QScopedPointer<AdaptersLauncher> m_adaptersLauncher;

    double m_stepSize = 0;

    void setupHardwareDriver();

    /// Проводит начальную настройку виджетов
    void setupWidgets();

    /// Блокирует и скрывает виджеты, которые не нужны в данной сборке, но нужны в принципе
    void hideWidgets();

    /// Подключает необходимые слоты к полям и сигналам
    void setupSlots();

    /// Отключает слоты от полей и сигналов
    void resetSlots();

private slots:
    void updateBatteryStatusDisplay();
    Q_NORETURN void on_exit_action_triggered();
    void on_syntaxHighlightingCheckBox_clicked();

    void on_saveSettingsPushButton_clicked();

    void on_movementXPositivePushButton_pressed();
    void on_movementXPositivePushButton_released();

    void on_movementXNegativePushButton_pressed();
    void on_movementXNegativePushButton_released();

    void on_movementYPositivePushButton_pressed();
    void on_movementYPositivePushButton_released();

    void on_movementYNegativePushButton_pressed();
    void on_movementYNegativePushButton_released();

    void on_movementXNegativeYPositivePushButton_pressed();
    void on_movementXNegativeYPositivePushButton_released();

    void on_movementXNegativeYNegativePushButton_pressed();
    void on_movementXNegativeYNegativePushButton_released();

    void on_movementXPositiveYPositivePushButton_pressed();
    void on_movementXPositiveYPositivePushButton_released();

    void on_movementXPositiveYNegativePushButton_pressed();
    void on_movementXPositiveYNegativePushButton_released();

    void on_movementZPositivePushButton_pressed();
    void on_movementZPositivePushButton_released();

    void on_movementZNegativePushButton_pressed();
    void on_movementZNegativePushButton_released();

    void on_movementANegativePushButton_pressed();
    void on_movementANegativePushButton_released();

    void on_movementAPositivePushButton_pressed();
    void on_movementAPositivePushButton_released();

    void on_movementBNegativePushButton_pressed();
    void on_movementBNegativePushButton_released();

    void on_movementBPositivePushButton_pressed();
    void on_movementBPositivePushButton_released();

    void on_movementCNegativePushButton_pressed();
    void on_movementCNegativePushButton_released();

    void on_movementCPositivePushButton_pressed();
    void on_movementCPositivePushButton_released();

    void on_movementUNegativePushButton_pressed();
    void on_movementUNegativePushButton_released();

    void on_movementUPositivePushButton_pressed();
    void on_movementUPositivePushButton_released();

    void on_movementVNegativePushButton_pressed();
    void on_movementVNegativePushButton_released();

    void on_movementVPositivePushButton_pressed();
    void on_movementVPositivePushButton_released();

    void on_movementWNegativePushButton_pressed();
    void on_movementWNegativePushButton_released();

    void on_movementWPositivePushButton_pressed();
    void on_movementWPositivePushButton_released();

    void on_discreteRadioButton_1_clicked();

    void on_discreteRadioButton_2_clicked();

    void on_discreteRadioButton_3_clicked();

    void on_discreteRadioButton_4_clicked();

    void on_discreteRadioButton_5_clicked();

private:
    void fillSettings();
    QList<AxisPushButton*> getAllAxesButtons();
    void setAxesButtonsState(bool enable);
    void setAdjustmentActionsButtonsState(bool enable);
    void stopContiniousMovement();
};


#endif // MAINWINDOW_H

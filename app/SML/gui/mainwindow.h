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
#include "gui/utils/gcodes_syntax_highlighter.h"
#include "models/hardware/hardware_driver.h"
#include "gui/widgets/spindel_control_widget.h"

#include "models/services/gcodes/view/gcodes_view_interactor.h"
#include "./models/services/adapters/launcher/adapters_launcher.h"

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

    QList<QMetaObject::Connection> m_slotsInfo;

    /// Подсветки синтаксиса в редакторе G-кодов
    QScopedPointer<GCodesSyntaxHighlighter> m_hightlighter;
    QScopedPointer<AdaptersLauncher> m_adaptersLauncher;

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
};


#endif // MAINWINDOW_H

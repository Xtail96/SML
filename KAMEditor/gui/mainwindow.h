#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <set>
#include <tuple>
#include <vector>

#include <QMainWindow>
#include <QTimer>
#include <QShortcut>
#include <QKeySequence>
#include <QList>
#include <QMessageBox>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "machinetool.h"
#include "commandinterpreter.h"
#include "points/addpointdialog.h"
#include "points/mousetoselectionpointdialog.h"
#include "points/editpointdialog.h"

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



    void setupShortcuts();

    void disableMovementButtonsShortcuts();
    void enableMovementButtonsShortcuts();

    void setMovementButtonsShortcutsState(bool state);
    void setMovementButtonsRepeatState(bool state);

    void update_coordinates();
    //void update_points();
    void update_battery_status();
    void update_kabriol_avaliability();


protected:
    void update_points();

private slots:

    void update();
    void on_discrete_radio_button_1_clicked();
    void on_discrete_radio_button_2_clicked();
    void on_discrete_radio_button_3_clicked();
    void on_discrete_radio_button_4_clicked();
    void on_discrete_radio_button_5_clicked();

    void on_movement_x_positive_button_clicked();
    void on_movement_x_negative_button_clicked();
    void on_movement_y_positive_button_clicked();
    void on_movement_y_negative_button_clicked();

    void on_movement_x_positive_y_positive_button_clicked();
    void on_movement_x_positive_y_negative_button_clicked();
    void on_movement_x_negative_y_positive_button_clicked();
    void on_movement_x_negative_y_negative_button_clicked();

    void on_movement_z_negative_button_clicked();
    void on_movement_z_positive_button_clicked();

    void on_movement_a_positive_button_clicked();
    void on_movement_a_negative_button_clicked();


    void on_movement_b_positive_button_clicked();
    void on_movement_b_negative_button_clicked();

    void on_feedrate_scroll_bar_valueChanged(int value);

    void on_rotations_scroll_bar_valueChanged(int value);

    void on_exit_action_triggered();

    void on_point_amount_button_clicked();
    void on_park_button_clicked();
    void on_point_add_button_clicked();
    void on_point_delete_button_clicked();
    void on_zero_button_clicked();
    void on_point_cursor_button_clicked();
    void on_point_edit_button_clicked();
    void on_point_copy_button_clicked();
};


#endif // MAINWINDOW_H

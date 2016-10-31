#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QShortcut>
#include <QList>
#include <QMessageBox>
#include <vector>
#include <windows.h>

#include "basemachinetool.h"

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

    std::vector<Vector3D> points;

    void update_coordinates();
    void update_battery_status();

    void setMovementButtonsRepeatState(bool state);


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


    void on_feedrate_scroll_bar_valueChanged(int value);

    void on_rotations_scroll_bar_valueChanged(int value);

    void on_exit_action_triggered();

    void on_point_amount_button_clicked();
    void on_movement_a_posititve_button_clicked();
    void on_movement_a_negative_button_clicked();
};


#endif // MAINWINDOW_H

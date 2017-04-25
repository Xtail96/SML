#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>

#include <set>
#include <tuple>
#include <vector>

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

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include "machinetool.h"
#include "pointsmanager.h"
#include "points/addpointdialog.h"
#include "points/mousetoselectionpointdialog.h"
#include "points/editpointdialog.h"
#include "commandinterpreter.h"
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

#include "gcodessyntaxhighlighter.h"


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



    void setupDimensions();
    void setupDirections();
    void setupKinematicsSettings();

    void setUpElectricalSettings();

    void dimensionsRecovery();
    void directionsRecovery();
    void kinematicsSettingsRecovery();
    void electricialSettingsRecovery();


    void editSettingsField(QLineEdit *qle);
    void applySettingsField(QLineEdit *qle);

    void setupShortcuts(); 
    void setupEditorShortcuts();

    void disableMovementButtonsShortcuts();
    void enableMovementButtonsShortcuts();

    void setMovementButtonsShortcutsState(bool state);
    void setMovementButtonsRepeatState(bool state);

    void update_coordinates();
    void update_battery_status();
    void update_kabriol_avaliability();

    void update_edges_control_status();

    void setSelectedCommandVectorNumber(unsigned int& current_row);

    std::vector<QLineEdit*> makeQLineEditVector(int tmp);
    std::vector<QCheckBox*> makeQCheckBoxVector(int tmp);

    void parse7kamToSml(QString &tmp);
    void parse7kamToSmlStep(std::string &tmp);
    void setCommandArguments(std::string s, Command &command);

protected:
    void update_points();
    void update_commands();
    void update_base_status();

private slots:

    void addLineCommand();
    void deleteCommand();

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
    void on_commands_tools_listWidget_doubleClicked(const QModelIndex &index);
    void on_to_base_button_clicked();
    void on_edges_contol_check_box_clicked();
    void on_spindle_enable_pushButton_clicked();
    void on_mill_warming_pushButton_clicked();
    void on_points_table_widget_doubleClicked(const QModelIndex &index);
    void on_sml_editor_treeWidget_doubleClicked(const QModelIndex &index);
    void on_sml_editor_treeWidget_clicked(const QModelIndex &index);
    void on_open_action_triggered();
    void on_change_mechanics_settings_pushButton_clicked();
    void on_apply_mechanics_settings_pushButton_clicked();
    void on_cancel_mechanical_settings_pushButton_clicked();
    void on_change_elecrical_settings_pushButton_clicked();
    void on_apply_electrical_settings_pushButton_clicked();
    void on_cancel_electrical_settings_pushButton_clicked();
    void on_gcodes_editor_textEdit_textChanged();
};


#endif // MAINWINDOW_H

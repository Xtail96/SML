#ifndef TOOLLENGTHSENSORWINDOW_H
#define TOOLLENGTHSENSORWINDOW_H

#include <QDialog>

namespace Ui {
class ToolLengthSensorWindow;
}

class ToolLengthSensorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ToolLengthSensorWindow(QWidget *parent = 0);
    ~ToolLengthSensorWindow();

private:
    Ui::ToolLengthSensorWindow *ui;
};

#endif // TOOLLENGTHSENSORWINDOW_H

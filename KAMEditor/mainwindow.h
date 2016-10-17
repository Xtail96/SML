#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>

#include "machinetool.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void update();


private:
    Ui::MainWindow *ui;
    QTimer *timer;

    void update_coordinates();
};


#endif // MAINWINDOW_H

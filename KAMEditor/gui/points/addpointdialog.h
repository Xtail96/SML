#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include "models/machinetool/pointsmanager/pointsmanager.h"

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(MainWindowController *_controller, QWidget *parent = 0);
    explicit AddPointDialog(MainWindowController *_controller, unsigned int _pointNumber, QWidget *parent);
    ~AddPointDialog();
signals:
    void newPoint(QStringList coordinates);
    void updatePointsCoordinates(QStringList coordinates, unsigned int number);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
    void setupFields();

    MainWindowController* controller;

    bool isEdit;
    unsigned int pointNumber;
};

#endif // ADDPOINTDIALOG_H

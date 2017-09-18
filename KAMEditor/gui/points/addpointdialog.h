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
    //explicit AddPointDialog(MovementsHandler *_movementsHandler, PointsManager *_pointsManager, std::shared_ptr<Point> pointForEdit, unsigned int _pointNumber, QWidget *parent = 0);
    ~AddPointDialog();
signals:
    void newPoint(Point* p);
    void updatePoint(Point* p, unsigned int number);

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

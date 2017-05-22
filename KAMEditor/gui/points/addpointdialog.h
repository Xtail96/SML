#ifndef ADDPOINTDIALOG_H
#define ADDPOINTDIALOG_H

#include <QDialog>
#include "pointsManager/pointsmanager.h"
#include "point/point.h"

namespace Ui {
class AddPointDialog;
}

class AddPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPointDialog(QWidget *parent = 0);
    ~AddPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddPointDialog *ui;
};

#endif // ADDPOINTDIALOG_H

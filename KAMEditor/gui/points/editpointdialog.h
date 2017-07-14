#ifndef EDITPOINTDIALOG_H
#define EDITPOINTDIALOG_H

#include <QDialog>
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/pointsmanager/point/point.h"

namespace Ui {
class EditPointDialog;
}

class EditPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPointDialog(QWidget *parent = 0);
    ~EditPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditPointDialog *ui;
};

#endif // EDITPOINTDIALOG_H

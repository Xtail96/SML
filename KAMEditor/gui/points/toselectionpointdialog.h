#ifndef TOSELECTIONPOINTDIALOG_H
#define TOSELECTIONPOINTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "models/machinetool/pointsmanager/pointsmanager.h"
#include "models/machinetool/pointsmanager/point/point.h"

namespace Ui {
class ToSelectionPointDialog;
}

class ToSelectionPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToSelectionPointDialog(QWidget *parent = 0);
    ~ToSelectionPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ToSelectionPointDialog *ui;
};

#endif // MOUSETOSELECTIONPOINTDIALOG_H

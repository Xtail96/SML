#ifndef MOUSETOSELECTIONPOINTDIALOG_H
#define MOUSETOSELECTIONPOINTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "pointsmanager.h"
#include "point.h"

namespace Ui {
class MouseToSelectionPointDialog;
}

class MouseToSelectionPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MouseToSelectionPointDialog(QWidget *parent = 0);
    ~MouseToSelectionPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MouseToSelectionPointDialog *ui;
};

#endif // MOUSETOSELECTIONPOINTDIALOG_H
#ifndef MOUSETOSELECTIONPOINTDIALOG_H
#define MOUSETOSELECTIONPOINTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "machinetool/components/pointsManager/pointsManager/pointsmanager.h"
#include "machinetool/components/pointsManager/point/point.h"

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

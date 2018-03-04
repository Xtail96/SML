#ifndef TOSELECTIONPOINTDIALOG_H
#define TOSELECTIONPOINTDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>

namespace Ui {
class ToSelectionPointDialog;
}

class ToSelectionPointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ToSelectionPointDialog(QTableWidget* _currentTableWidget, QWidget *parent = 0);
    ~ToSelectionPointDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ToSelectionPointDialog *ui;
    QTableWidget* currentTableWidget;
};

#endif // MOUSETOSELECTIONPOINTDIALOG_H

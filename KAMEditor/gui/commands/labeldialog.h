#ifndef LABELDIALOG_H
#define LABELDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class LabelDialog;
}

class LabelDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit LabelDialog(QWidget *parent = 0);
    ~LabelDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::LabelDialog *ui;
};

#endif // LABELDIALOG_H

#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"

namespace Ui {
class RotateDialog;
}

class RotateDialog : public QDialog, private CommandDialog
{
    Q_OBJECT

public:
    explicit RotateDialog(QWidget *parent = 0);
    ~RotateDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::RotateDialog *ui;

    void fillFields();
};

#endif // ROTATEDIALOG_H

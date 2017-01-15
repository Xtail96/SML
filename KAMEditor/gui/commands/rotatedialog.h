#ifndef ROTATEDIALOG_H
#define ROTATEDIALOG_H

#include <QDialog>
#include "commandinterpreter.h"

namespace Ui {
class RotateDialog;
}

class RotateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RotateDialog(QWidget *parent = 0);
    ~RotateDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RotateDialog *ui;
};

#endif // ROTATEDIALOG_H

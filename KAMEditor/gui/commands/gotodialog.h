#ifndef GOTODIALOG_H
#define GOTODIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"

namespace Ui {
class GoToDialog;
}

class GoToDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoToDialog(QWidget *parent = 0);
    ~GoToDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GoToDialog *ui;
};

#endif // GOTODIALOG_H

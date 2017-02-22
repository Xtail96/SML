#ifndef ONDIALOG_H
#define ONDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"

namespace Ui {
class OnDialog;
}

class OnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnDialog(QWidget *parent = 0);
    ~OnDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OnDialog *ui;
};

#endif // ONDIALOG_H
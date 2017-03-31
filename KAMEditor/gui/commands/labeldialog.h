#ifndef LABELDIALOG_H
#define LABELDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"

namespace Ui {
class LabelDialog;
}

class LabelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LabelDialog(QWidget *parent = 0);
    ~LabelDialog();

private slots:
    void on_buttonBox_accepted();

    void on_LabelDialog_rejected();

private:
    Ui::LabelDialog *ui;
};

#endif // LABELDIALOG_H

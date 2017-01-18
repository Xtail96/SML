#ifndef OFFDIALOG_H
#define OFFDIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include "commandinterpreter.h"

namespace Ui {
class OffDialog;
}

class OffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OffDialog(QWidget *parent = 0);
    ~OffDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::OffDialog *ui;
};

#endif // OFFDIALOG_H

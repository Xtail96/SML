#ifndef ARCDIALOG_H
#define ARCDIALOG_H

#include <QDialog>

#include "commandinterpreter.h"

namespace Ui {
class ArcDialog;
}

class ArcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArcDialog(QWidget *parent = 0);
    ~ArcDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ArcDialog *ui;
};

#endif // ARCDIALOG_H

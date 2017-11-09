#ifndef VELOCITYDIALOG_H
#define VELOCITYDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class VelocityDialog;
}

class VelocityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VelocityDialog(QWidget *parent = 0);
    ~VelocityDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VelocityDialog *ui;
};

#endif // VELOCITYDIALOG_H

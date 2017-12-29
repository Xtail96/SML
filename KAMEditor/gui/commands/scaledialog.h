#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ScaleDialog;
}

class ScaleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleDialog(QWidget *parent = 0);
    ~ScaleDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ScaleDialog *ui;

    void fillFields();
};

#endif // SCALEDIALOG_H

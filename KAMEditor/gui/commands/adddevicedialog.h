#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>

namespace Ui {
class AddDeviceDialog;
}

class AddDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDeviceDialog(QWidget *parent = 0);
    ~AddDeviceDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddDeviceDialog *ui;
};

#endif // ADDDEVICEDIALOG_H

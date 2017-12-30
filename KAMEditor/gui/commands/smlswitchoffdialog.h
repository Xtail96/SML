#ifndef OFFDIALOG_H
#define OFFDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLSwitchOffDialog;
}

class SMLSwitchOffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLSwitchOffDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLSwitchOffDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::SMLSwitchOffDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // OFFDIALOG_H

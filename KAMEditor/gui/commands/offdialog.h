#ifndef OFFDIALOG_H
#define OFFDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "commanddialog.h"
#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class OffDialog;
}

class OffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OffDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~OffDialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::OffDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // OFFDIALOG_H

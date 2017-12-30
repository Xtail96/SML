#ifndef PAUSEDIALOG_H
#define PAUSEDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLPauseDialog;
}

class SMLPauseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLPauseDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLPauseDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SMLPauseDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // PAUSEDIALOG_H

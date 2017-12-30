#ifndef TTTARCDIALOG_H
#define TTTARCDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "controllers/mainwindowcontroller/mainwindowcontroller.h"

namespace Ui {
class SMLTTTArcDialog;
}

class SMLTTTArcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLTTTArcDialog(MainWindowController* _controller, size_t _index, QWidget *parent = 0, bool _edit = false);
    ~SMLTTTArcDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SMLTTTArcDialog *ui;
    MainWindowController* controller;
    size_t index;
    bool edit;

    void fillFields();
};

#endif // TTTARCDIALOG_H

#ifndef SMLCONSOLEDIALOG_H
#define SMLCONSOLEDIALOG_H

#include <QDialog>

#include "presenters/mainwindowpresenter/mainwindowpresenter.h"

namespace Ui {
class SMLConsoleDialog;
}

class SMLConsoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SMLConsoleDialog(MainWindowPresenter* controller, QWidget *parent = 0);
    ~SMLConsoleDialog();
protected:
    void setup();
private:
    Ui::SMLConsoleDialog *ui;
    MainWindowPresenter *m_controller;

protected slots:
    void sendCommang(QString cmd);
    void handleCommand(QString cmd);
    void printResult(QString result);
    void handleMachineToolDisconnected(QString message);
};

#endif // SMLCONSOLEDIALOG_H

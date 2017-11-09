#ifndef ARC2DIALOG_H
#define ARC2DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Arc2Dialog;
}

class Arc2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Arc2Dialog(QWidget *parent = 0);
    ~Arc2Dialog();

private slots:
    void on_buttonBox_accepted();
private:
    Ui::Arc2Dialog *ui;
};

#endif // ARC2DIALOG_H

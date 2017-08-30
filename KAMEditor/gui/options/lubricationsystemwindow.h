#ifndef LUBRICATIONSYSTEMWINDOW_H
#define LUBRICATIONSYSTEMWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class LubricationSystemWindow;
}

class LubricationSystemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LubricationSystemWindow(QWidget *parent = 0);
    ~LubricationSystemWindow();

private slots:
    void on_lubricatePushButton_clicked();
    void stop();
    void updateProgressBar();

private:
    Ui::LubricationSystemWindow *ui;

    QTimer* generalLubricationTimer;
    QTimer* stepLubriactionTimer;
};

#endif // LUBRICATIONSYSTEMWINDOW_H

#ifndef LUBRICATIONSYSTEMWINDOW_H
#define LUBRICATIONSYSTEMWINDOW_H

#include <QDialog>

namespace Ui {
class LubricationSystemWindow;
}

class LubricationSystemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LubricationSystemWindow(QWidget *parent = 0);
    ~LubricationSystemWindow();

private:
    Ui::LubricationSystemWindow *ui;
};

#endif // LUBRICATIONSYSTEMWINDOW_H

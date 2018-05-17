#ifndef KABRIOLWINDOW_H
#define KABRIOLWINDOW_H

#include <QDialog>

namespace Ui {
class KabriolWindow;
}

class KabriolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit KabriolWindow(QWidget *parent = 0);
    ~KabriolWindow();

private:
    Ui::KabriolWindow *ui;
};

#endif // KABRIOLWINDOW_H

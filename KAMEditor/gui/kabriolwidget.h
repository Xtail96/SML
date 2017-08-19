#ifndef KABRIOLWIDGET_H
#define KABRIOLWIDGET_H

#include <QWidget>

namespace Ui {
class kabriolWidget;
}

class kabriolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit kabriolWidget(QWidget *parent = 0);
    ~kabriolWidget();

private:
    Ui::kabriolWidget *ui;
};

#endif // KABRIOLWIDGET_H

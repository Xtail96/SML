#ifndef SMLLISTWIDGET_H
#define SMLLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QGroupBox>

class SMLListWidget : public QListWidget
{
public:
    SMLListWidget(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *keyEvent);
};

#endif // SMLLISTWIDGET_H

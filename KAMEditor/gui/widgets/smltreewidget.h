#ifndef SMLTREEWIDGET_H
#define SMLTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QKeyEvent>

#include <QDebug>

class SMLTreeWidget : public QTreeWidget
{
public:
    SMLTreeWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyEvent);
};

#endif // SMLTREEWIDGET_H

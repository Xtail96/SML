#ifndef SMLTREEWIDGET_H
#define SMLTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QAbstractItemView>

#include <QDebug>

class SMLTreeWidget : public QTreeWidget
{
    Q_OBJECT
signals:
    void copySignal();
    void cutSignal();
    void pasteSignal();
    void undoSignal();
    void eraseSignal();
public:
    SMLTreeWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyEvent);
};

#endif // SMLTREEWIDGET_H

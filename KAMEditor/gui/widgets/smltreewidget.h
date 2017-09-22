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
    void copySignal(QModelIndexList itemsIndexes);
    void cutSignal(QModelIndexList itemsIndexes);
    void pasteSignal(QModelIndex itemIndex);
    void undoSignal();
    void eraseSignal(QModelIndexList indexes);
public:
    SMLTreeWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyEvent);
private:
    void keyReturnPressed(QModelIndexList itemsIndexes);
    void keyBackspacePressed(QModelIndexList itemsIndexes);
    void keyUpPressed(QModelIndexList itemsIndexes);
    void keyDownPressed(QModelIndexList itemsIndexes);
    void keysCtrlAPressed();
    void keysCtrlCPressed(QModelIndexList itemsIndexes);
    void keysCtrlXPressed(QModelIndexList itemsIndexes);
    void keysCtrlVPressed(QModelIndexList itemsIndexes);
    void keysCtrlZPressed();
    void keyEscapePressed();
    void updateSelectionMode(Qt::KeyboardModifiers modifiers);

};

#endif // SMLTREEWIDGET_H

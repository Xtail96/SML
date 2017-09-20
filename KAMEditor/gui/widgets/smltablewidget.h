#ifndef SMLTABLEWIDGET_H
#define SMLTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QKeyEvent>
#include <QAbstractItemView>

#include <QDebug>

class SMLTableWidget : public QTableWidget
{
    Q_OBJECT
signals:
    void addSignal();
    void editSignal(QModelIndex index);
    void eraseSignal(QModelIndexList indexes);

    void copySignal();
    void cutSignal();
    void pasteSignal();
public:
    SMLTableWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyEvent);
    static QModelIndexList getRowsIndexes(QModelIndexList itemsIndexes);
private:
    void keyReturnPressed(QModelIndexList selectedRowsIndexes);
    void keyBackspacePressed(QModelIndexList selectedRowsIndexes);
    void keyUpPressed(QModelIndexList selectedRowsIndexes);
    void keyDownPressed(QModelIndexList selectedRowsIndexes);
    void keysCtrlAPressed();
    void selectFirstRow();
};

#endif // SMLTABLEWIDGET_H

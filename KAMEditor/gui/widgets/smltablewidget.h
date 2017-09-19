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
    void editSignal(int row);
    void eraseSignal(QList<int> rows);

    void copySignal();
    void cutSignal();
    void pasteSignal();
public:
    SMLTableWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *keyEvent);
};

#endif // SMLTABLEWIDGET_H

#ifndef SMLLISTWIDGET_H
#define SMLLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QGroupBox>

class SMLListWidget : public QListWidget
{
    Q_OBJECT

public:
    SMLListWidget(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *keyEvent);
private:
    /*!
     * \brief Обрабатывает нажатие клавиши Return (ввод) на клавиатуре
     * \param selectedItemIndex список индексов выбранных рядов в таблице
     */
    void keyReturnPressed(QModelIndex selectedItemIndex);

    /*!
     * \brief Обрабатывает нажатие клавиши Up (стрелки вверх) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyUpPressed(QModelIndex selectedItemIndex);

    /*!
     * \brief Обрабатывает нажатие клавиши Down (стрелки вниз) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyDownPressed(QModelIndex selectedItemIndex);
};

#endif // SMLLISTWIDGET_H

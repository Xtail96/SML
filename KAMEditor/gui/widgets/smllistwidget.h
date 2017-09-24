#ifndef SMLLISTWIDGET_H
#define SMLLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QGroupBox>

/*!
 * \brief Класс Виджет SML-списка
 * Наследник QListWidget
 */
class SMLListWidget : public QListWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса Виджет SML-Списка
     * \param parent родительский виджет
     */
    SMLListWidget(QWidget *parent = 0);

    /*!
     * \brief Обрабатывает нажатие клавиши на клавиатуре
     * \param keyEvent событие нажатия клавиши на клавиатуре
     */
    void keyPressEvent(QKeyEvent *keyEvent);
private:
    /*!
     * \brief Обрабатывает нажатие клавиши Return (ввод) на клавиатуре
     * \param selectedItemIndex индекс выбранного элемента списка
     */
    void keyReturnPressed(QModelIndex selectedItemIndex);

    /*!
     * \brief Обрабатывает нажатие клавиши Up (стрелки вверх) на клавиатуре
     * \param selectedItemIndex индекс выбранного элемента списка
     */
    void keyUpPressed(QModelIndex selectedItemIndex);

    /*!
     * \brief Обрабатывает нажатие клавиши Down (стрелки вниз) на клавиатуре
     * \param selectedItemIndex индекс выбранного элемента списка
     */
    void keyDownPressed(QModelIndex selectedItemIndex);
};

#endif // SMLLISTWIDGET_H

#ifndef SMLTREEWIDGET_H
#define SMLTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QAbstractItemView>

#include <QDebug>

/*!
 * \brief Класс Виджет SML-Дерева
 * Наследник QTreeWidget
 */
class SMLTreeWidget : public QTreeWidget
{
    Q_OBJECT
signals:
    /*!
     * \brief Копировать
     * \param itemsIndexes индексы копируемых элементов
     */
    void copySignal(QModelIndexList itemsIndexes);

    /*!
     * \brief Вырезать
     * \param itemsIndexes индексы вырезаемых элементов
     */
    void cutSignal(QModelIndexList itemsIndexes);

    /*!
     * \brief Удалить
     * \param itemsIndexes индексы удаляемых элементов
     */
    void eraseSignal(QModelIndexList itemsIndexes);

    /*!
     * \brief Вставить
     * \param itemIndex индекс элемента, перед которым нужно выполнить вставку
     */
    void pasteSignal(QModelIndex itemIndex);
public:
    /*!
     * \brief Конструктор класса Виджет SML-Дерева
     * \param parent родительский виджет
     */
    SMLTreeWidget(QWidget *parent = 0);

    /*!
     * \brief Обрабатывает нажатие клавиши на клавиатуре
     * \param keyEvent событие нажатия клавиши
     */
    void keyPressEvent(QKeyEvent *keyEvent);

    /*!
     * \brief Получает индексы рядов по модельным индексам элементов
     * \param itemsIndexes модельные индексы элементов
     * \return список индексов рядов
     * Является статическим методом
     */
    static QModelIndexList getRowsIndexes(QModelIndexList itemsIndexes);
private:
    void selectFirstItem();
    void keyReturnPressed(QModelIndexList itemsIndexes);
    void keyBackspacePressed(QModelIndexList itemsIndexes);
    void keyUpPressed(QModelIndexList itemsIndexes);
    void keyDownPressed(QModelIndexList itemsIndexes);
    void keysCtrlAPressed();
    void keysCtrlCPressed(QModelIndexList itemsIndexes);
    void keysCtrlXPressed(QModelIndexList itemsIndexes);
    void keysCtrlVPressed(QModelIndexList itemsIndexes);
    void keyEscapePressed(QModelIndexList itemsIndexes);
    void updateSelectionMode(Qt::KeyboardModifiers modifiers);

};

#endif // SMLTREEWIDGET_H

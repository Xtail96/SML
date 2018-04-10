#ifndef SMLEDITORTREEWIDGET_H
#define SMLEDITORTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QKeyEvent>
#include <QAbstractItemView>

#include <QDebug>

/*!
 * \brief Класс Виджет Дерева SML-редактора
 * Наследник QTreeWidget
 */
class SMLEditorTreeWidget : public QTreeWidget
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
    SMLEditorTreeWidget(QWidget *parent = 0);

    /*!
     * \brief Обрабатывает нажатие клавиши на клавиатуре
     * \param keyEvent событие нажатия клавиши на клавиатуре
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
    /*!
     * \brief Выделяет первый элемент в дереве
     */
    void selectFirstItem();

    /*!
     * \brief Выделяет последний элемент в дереве
     */
    void selectLastItem();

    /*!
     * \brief Обрабаотывает нажатие клавиши Return (ввод) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keyReturnPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабаотывает нажатие клавиши Backspace (назад) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keyBackspacePressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабаотывает нажатие клавиши Up (стрелки вверх) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keyUpPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабаотывает нажатие клавиши Down (стрелки вниз) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keyDownPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабатывает нажатие сочетания клвишь Ctrl + A (одновременное нажатие клавиши Контрол и английской буквы A) на клавиатуре
     */
    void keysCtrlAPressed();

    /*!
     * \brief Обрабатывает нажатие сочетания клвишь Ctrl + C (одновременное нажатие клавиши Контрол и английской буквы C) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keysCtrlCPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабатывает нажатие сочетания клвишь Ctrl + X (одновременное нажатие клавиши Контрол и английской буквы X) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keysCtrlXPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабатывает нажатие сочетания клвишь Ctrl + V (одновременное нажатие клавиши Контрол и английской буквы V) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keysCtrlVPressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обрабатывает нажатие клвиши Escape (выход) на клавиатуре
     * \param itemsIndexes список индексов элементов
     */
    void keyEscapePressed(QModelIndexList itemsIndexes);

    /*!
     * \brief Обновляет состояние модификаторов клавиатуры (Ctrl, Shift)
     * \param modifiers модификаторы клавиатуры
     */
    void updateSelectionMode(Qt::KeyboardModifiers modifiers);

};

#endif // SMLEDITORTREEWIDGET_H

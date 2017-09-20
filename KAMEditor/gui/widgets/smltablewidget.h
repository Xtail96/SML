#ifndef SMLTABLEWIDGET_H
#define SMLTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QKeyEvent>
#include <QAbstractItemView>

#include <QDebug>

/*!
 * \brief Класс Виджет SML-Таблицы
 * Наследник QTableWidget
 */
class SMLTableWidget : public QTableWidget
{
    Q_OBJECT
signals:
    /*!
     * \brief Сигнал добавления точки
     */
    void addSignal();

    /*!
     * \brief Сигнал редактирования точки
     * \param index индекс редактируемой точки в таблице
     */
    void editSignal(QModelIndex index);

    /*!
     * \brief Сигнал удаления точек
     * \param indexes список индексов удаляемых точек в таблице
     */
    void eraseSignal(QModelIndexList indexes);

    /*!
     * \brief Сигнал копирования точки
     */
    void copySignal();

    /*!
     * \brief Сигнал вставки точки
     */
    void pasteSignal();
public:
    /*!
     * \brief Конструктор класса Виджет SML-Таблицы
     * \param parent
     */
    SMLTableWidget(QWidget *parent = 0);

    /*!
     * \brief Обрабатывает нажатие клавиши на клавиатуре внутри виджета
     * \param keyEvent событие надатия клавиши на клавиатуре
     */
    void keyPressEvent(QKeyEvent *keyEvent);

    /*!
     * \brief Получает список индексов рядов таблицы по списку индексов элементов
     * \param itemsIndexes список индексов элементов
     * \return список индексов рядов таблицы
     * \attention Является статическим методом
     */
    static QModelIndexList getRowsIndexes(QModelIndexList itemsIndexes);
private:
    /*!
     * \brief Обрабатывает нажатие клавиши Return (ввод) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyReturnPressed(QModelIndexList selectedRowsIndexes);

    /*!
     * \brief Обрабатывает нажатие клавиши Backspace (назад) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyBackspacePressed(QModelIndexList selectedRowsIndexes);

    /*!
     * \brief Обрабатывает нажатие клавиши Up (стрелки вверх) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyUpPressed(QModelIndexList selectedRowsIndexes);

    /*!
     * \brief Обрабатывает нажатие клавиши Down (стрелки вниз) на клавиатуре
     * \param selectedRowsIndexes список индексов выбранных рядов в таблице
     */
    void keyDownPressed(QModelIndexList selectedRowsIndexes);

    /*!
     * \brief Обрабатывает нажатия сочетания клавишь Ctrl + A (одновременное нажатие клавиши Контрол и клавиши английской буквы A) на клавиатуре
     */
    void keysCtrlAPressed();

    /*!
     * \brief Делает первый ряд таблицы текущим
     */
    void selectFirstRow();
};

#endif // SMLTABLEWIDGET_H

#include "smleditortreewidget.h"

SMLEditorTreeWidget::SMLEditorTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{

}

void SMLEditorTreeWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QModelIndexList selectedItemsIndexes = this->selectionModel()->selectedIndexes();
    if(selectedItemsIndexes.size() > 0)
    {
        QModelIndexList selectedRowsIndexes = getRowsIndexes(selectedItemsIndexes);

        int keyPressed = keyEvent->key();
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        updateSelectionMode(modifiers);

        switch (keyPressed) {
        case Qt::Key_Return:
        {
            keyReturnPressed(selectedRowsIndexes);
            break;
        }
        case Qt::Key_Backspace:
        {
            keyBackspacePressed(selectedRowsIndexes);
            break;
        }
        case Qt::Key_Escape:
        {
            keyEscapePressed(selectedRowsIndexes);
            break;
        }
        case Qt::Key_Up:
        {
            keyUpPressed(selectedRowsIndexes);
            break;
        }
        case Qt::Key_Down:
        {
            keyDownPressed(selectedRowsIndexes);
            break;
        }
        case Qt::Key_A:
        {
            if(modifiers == Qt::ControlModifier)
            {
                keysCtrlAPressed();
            }
            break;
        }
        case Qt::Key_C:
        {
            if(modifiers == Qt::ControlModifier)
            {
                keysCtrlCPressed(selectedRowsIndexes);
            }
            break;
        }
        case Qt::Key_X:
        {
            if(modifiers == Qt::ControlModifier)
            {
                keysCtrlXPressed(selectedRowsIndexes);
            }
            break;
        }
        case Qt::Key_V:
        {
            if(modifiers == Qt::ControlModifier)
            {
                keysCtrlVPressed(selectedRowsIndexes);
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
    else
    {
        if(this->topLevelItemCount() > 0)
        {
            selectFirstItem();
        }
    }
}

QModelIndexList SMLEditorTreeWidget::getRowsIndexes(QModelIndexList itemsIndexes)
{
    QModelIndexList rowsIndexes;
    for(auto index : itemsIndexes)
    {
        if(index.column() == 0)
        {
            rowsIndexes.push_back(index);
        }
    }
    return rowsIndexes;
}

void SMLEditorTreeWidget::selectFirstItem()
{
    QTreeWidgetItem* firstItem = this->topLevelItem(0);
    this->setCurrentItem(firstItem);
}

void SMLEditorTreeWidget::selectLastItem()
{
    int itemsCount = this->topLevelItemCount();
    QTreeWidgetItem* lastItem = this->topLevelItem(itemsCount - 1);
    this->setCurrentItem(lastItem);
}

void SMLEditorTreeWidget::keyReturnPressed(QModelIndexList itemsIndexes)
{
    QModelIndex firstSelectedItemIndex = itemsIndexes[0];
    if( (firstSelectedItemIndex.row() >= 0) && (firstSelectedItemIndex.row() < this->topLevelItemCount()) )
    {
        emit doubleClicked(firstSelectedItemIndex);
    }
}

void SMLEditorTreeWidget::keyBackspacePressed(QModelIndexList itemsIndexes)
{
    emit eraseSignal(itemsIndexes);
}

void SMLEditorTreeWidget::keyUpPressed(QModelIndexList itemsIndexes)
{
    QModelIndex firstSelectedItemIndex = itemsIndexes[0];
    int firstSelectedRow = firstSelectedItemIndex.row();
    if( (firstSelectedRow > 0) && (firstSelectedRow < this->topLevelItemCount()) )
    {
        this->setCurrentIndex(this->indexAbove(firstSelectedItemIndex));
    }
    else
    {
        if(firstSelectedRow == 0)
        {
            selectLastItem();
        }
    }
}

void SMLEditorTreeWidget::keyDownPressed(QModelIndexList itemsIndexes)
{
    QModelIndex lastSelectedItemIndex = itemsIndexes[itemsIndexes.size() - 1];
    int lastSelectedRow = lastSelectedItemIndex.row();
    if( (lastSelectedRow >= 0) && (lastSelectedRow < this->topLevelItemCount() - 1) )
    {
        this->setCurrentIndex(this->indexBelow(lastSelectedItemIndex));
    }
    else
    {
        if(lastSelectedRow == this->topLevelItemCount() - 1)
        {
            selectFirstItem();
        }
    }
}

void SMLEditorTreeWidget::keysCtrlAPressed()
{
    this->setSelectionMode(QAbstractItemView::MultiSelection);
    this->selectAll();
}

void SMLEditorTreeWidget::keysCtrlCPressed(QModelIndexList itemsIndexes)
{
    emit copySignal(itemsIndexes);
}

void SMLEditorTreeWidget::keysCtrlXPressed(QModelIndexList itemsIndexes)
{
    emit cutSignal(itemsIndexes);
}

void SMLEditorTreeWidget::keysCtrlVPressed(QModelIndexList itemsIndexes)
{
    QModelIndex firstSelectedItemIndex = itemsIndexes[0];
    emit pasteSignal(firstSelectedItemIndex);
}

void SMLEditorTreeWidget::keyEscapePressed(QModelIndexList itemsIndexes)
{
    if(itemsIndexes.size() <= 1)
    {
        this->setCurrentIndex(QModelIndex());
    }
    else
    {
        QModelIndex firstSelectedItemIndex = itemsIndexes[0];
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        this->setCurrentIndex(firstSelectedItemIndex);
    }
}

void SMLEditorTreeWidget::updateSelectionMode(Qt::KeyboardModifiers modifiers)
{
    switch (modifiers) {
    case Qt::ShiftModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    case Qt::ControlModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    case Qt::ShiftModifier | Qt::KeypadModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    case Qt::ControlModifier | Qt::KeypadModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    default:
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        break;
    }
}

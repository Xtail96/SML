#include "smltablewidget.h"

SMLTableWidget::SMLTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SMLTableWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QList<QTableWidgetItem*> selectedItems = this->selectedItems();
    QSet<int> selectedRows;
    for(auto selectedItem : selectedItems)
    {
        selectedRows.insert(selectedItem->row());
    }

    int keyPressed = keyEvent->key();
    int rowsCount = this->rowCount();

    switch (keyPressed) {
    case Qt::Key_Return:
    {
        if(*selectedRows.begin() >= 0 && *selectedRows.begin() < rowsCount)
        {
            emit editSignal(*selectedRows.begin());
        }
        break;
    }
    case Qt::Key_Backspace:
    {
        QList<int> selectedRowsList;
        for(auto row : selectedRows)
        {
            selectedRowsList.push_back(row);
        }
        emit eraseSignal(selectedRowsList);
        break;
    }
    case Qt::Key_Up:
    {
        //selectRow(up);
        break;
    }
    case Qt::Key_Down:
    {
        /*if(currentRow >= 0 && currentRow < rowsCount - 1)
        {
            this->setCurrentItem(this->itemBelow(selectedItem));
        }*/
        break;
    }
    /*case Qt::Key_A:
    {
        if(modifiers == Qt::ControlModifier)
        {
            this->selectAll();
        }
        break;
    }*/
    /*case Qt::Key_C:
    {
        if(modifiers == Qt::ControlModifier)
        {
            emit copySignal();
        }
        break;
    }
    case Qt::Key_X:
    {
        if(modifiers == Qt::ControlModifier)
        {
            emit cutSignal();
        }
        break;
    }
    case Qt::Key_V:
    {
        if(modifiers == Qt::ControlModifier)
        {
            emit pasteSignal();
        }
        break;
    }
    case Qt::Key_Z:
    {
        if(modifiers == Qt::ControlModifier)
        {
            emit undoSignal();
        }
        break;
    }
    case Qt::Key_Escape:
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        break;*/
    default:
    {
        break;
    }
    }
}

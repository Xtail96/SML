#include "smltablewidget.h"

SMLTableWidget::SMLTableWidget(QWidget *parent) :
    QTableWidget(parent)
{

}

void SMLTableWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QList<QTableWidgetItem*> selectedItems = this->selectedItems();
    QList<int> selectedRows;
    for(auto selectedItem : selectedItems)
    {
        selectedRows.push_back(selectedItem->row());
    }

    int keyPressed = keyEvent->key();
    int rowsCount = this->rowCount();

    switch (keyPressed) {
    case Qt::Key_Return:
    {
        if(selectedRows[0] >= 0 && selectedRows[0] < rowsCount)
        {
            emit editSignal(selectedRows[0]);
        }
        break;
    }
    case Qt::Key_Backspace:
    {
        emit eraseSignal(selectedRows);
        break;
    }
    /*case Qt::Key_Up:
    {
        if(selectedRows[0] > 0)
        {
            this->setCurrentIndex(QModelIndex());
        }
        break;
    }
    case Qt::Key_Down:
    {
        if(currentRow >= 0 && currentRow < rowsCount - 1)
        {
            this->setCurrentItem(this->itemBelow(selectedItem));
        }
        break;
    }*/
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

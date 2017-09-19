#include "smltablewidget.h"

SMLTableWidget::SMLTableWidget(QWidget *parent) :
    QTableWidget(parent)
{
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void SMLTableWidget::keyPressEvent(QKeyEvent *keyEvent)
{

    QModelIndexList selectedItemsIndexes = this->selectedIndexes();
    if(selectedItemsIndexes.size() > 0)
    {
        QModelIndexList selectedRowsIndexes = getRowsIndexes(selectedItemsIndexes);
        qSort(selectedRowsIndexes);

        int keyPressed = keyEvent->key();
        int rowsCount = this->rowCount();

        switch (keyPressed) {
        case Qt::Key_Return:
        {
            if(selectedRowsIndexes.begin()->row() >= 0 && selectedRowsIndexes.begin()->row() < rowsCount)
            {
                emit editSignal(*selectedRowsIndexes.begin());
            }
            break;
        }
        case Qt::Key_Backspace:
        {
            emit eraseSignal(selectedRowsIndexes);
            break;
        }
        case Qt::Key_Up:
        {
            //selectRow(up);
            break;
        }
        case Qt::Key_Down:
        {

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
}

QModelIndexList SMLTableWidget::getRowsIndexes(QModelIndexList itemsIndexes)
{
    QModelIndexList rowsIndexes = {*itemsIndexes.begin()};
    int currentItemRow = rowsIndexes.begin()->row();
    for(int i = 1; i < itemsIndexes.size(); i++)
    {
        if(itemsIndexes[i].row() != currentItemRow)
        {
            rowsIndexes.push_back(itemsIndexes[i]);
            currentItemRow = itemsIndexes[i].row();
        }
    }
    return rowsIndexes;
}

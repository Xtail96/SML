#include "smltreewidget.h"

SMLTreeWidget::SMLTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{

}

void SMLTreeWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QTreeWidgetItem *selectedItem = this->currentItem();
    int currentRow = this->currentIndex().row();
    int rowsCount = this->topLevelItemCount();

    int keyPressed = keyEvent->key();
    Qt::KeyboardModifiers modifiers = keyEvent->modifiers();

    switch (keyPressed) {
    case Qt::Key_Return:
    {
        if(currentRow >= 0 && currentRow < rowsCount)
        {
            emit itemDoubleClicked(selectedItem, 1);
        }
        break;
    }
    case Qt::Key_Up:
    {
        if(currentRow > 0)
        {
            this->setCurrentItem(this->itemAbove(selectedItem));
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
    }
    case Qt::Key_A:
    {
        if(modifiers == Qt::ControlModifier)
        {
            this->selectAll();
        }
    }
    default:
    {
        break;
    }
    }

}

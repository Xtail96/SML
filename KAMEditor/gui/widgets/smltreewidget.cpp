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
        else
        {
            if(currentRow == 0)
            {

            }
            else
            {

            }
        }
        break;
    }
    case Qt::Key_Down:
    {
        if(currentRow >= 0)
        {
            if(currentRow == rowsCount - 1)
            {

            }
            else
            {
                this->setCurrentItem(this->itemBelow(selectedItem));
            }
        }
        else
        {

        }
        break;
    }
    default:
    {
        break;
    }
    }

}

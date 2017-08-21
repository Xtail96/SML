#include "smllistwidget.h"

SMLListWidget::SMLListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void SMLListWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QListWidgetItem *selectedItem = this->currentItem();
    int currentRow = this->currentRow();
    int rowsCount = this->count();

    int keyPressed = keyEvent->key();

    switch (keyPressed) {
    case Qt::Key_Return:
    {
        if(currentRow >= 0 && currentRow < rowsCount)
        {
            emit itemClicked(selectedItem);
        }
        break;
    }
    case Qt::Key_Up:
    {
        if(currentRow > 0)
        {
            this->setCurrentRow(currentRow - 1);
        }
        else
        {
            if(currentRow == 0)
            {
                this->setCurrentRow(rowsCount - 1);
            }
            else
            {
                this->setCurrentRow(0);
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
                this->setCurrentRow(0);
            }
            else
            {
                this->setCurrentRow(currentRow + 1);
            }
        }
        else
        {
            this->setCurrentRow(rowsCount - 1);
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

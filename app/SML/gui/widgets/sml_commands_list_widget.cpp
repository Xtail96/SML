#include "sml_commands_list_widget.h"

SMLCommandsListWidget::SMLCommandsListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void SMLCommandsListWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QModelIndex selectedItemIndex = this->currentIndex();
    int keyPressed = keyEvent->key();

    switch (keyPressed) {
    case Qt::Key_Return:
    {
        keyReturnPressed(selectedItemIndex);
        break;
    }
    case Qt::Key_Up:
    {
        keyUpPressed(selectedItemIndex);
        break;
    }
    case Qt::Key_Down:
    {
        keyDownPressed(selectedItemIndex);
        break;
    }
    default:
    {
        break;
    }
    }
}

void SMLCommandsListWidget::keyReturnPressed(QModelIndex selectedItemIndex)
{
    int currentItemRow = selectedItemIndex.row();
    if(currentItemRow >= 0 && currentItemRow < this->count())
    {
        emit clicked(selectedItemIndex);
    }
}

void SMLCommandsListWidget::keyUpPressed(QModelIndex selectedItemIndex)
{
    int currentItemRow = selectedItemIndex.row();
    int rowsCount = this->count();
    if(currentItemRow > 0)
    {
        this->setCurrentRow(currentItemRow - 1);
    }
    else
    {
        if(currentItemRow == 0)
        {
            this->setCurrentRow(rowsCount - 1);
        }
        else
        {
            this->setCurrentRow(0);
        }
    }
}

void SMLCommandsListWidget::keyDownPressed(QModelIndex selectedItemIndex)
{
    int currentItemRow = selectedItemIndex.row();
    int rowsCount = this->count();
    if(currentItemRow >= 0)
    {
        if(currentItemRow == rowsCount - 1)
        {
            this->setCurrentRow(0);
        }
        else
        {
            this->setCurrentRow(currentItemRow + 1);
        }
    }
    else
    {
        this->setCurrentRow(rowsCount - 1);
    }
}

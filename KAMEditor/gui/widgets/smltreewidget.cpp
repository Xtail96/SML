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
    //qDebug() << modifiers;

    switch (modifiers) {
    case Qt::ControlModifier | Qt::KeypadModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    case Qt::ControlModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    case Qt::ShiftModifier:
        this->setSelectionMode(QAbstractItemView::MultiSelection);
        break;
    default:
        this->setSelectionMode(QAbstractItemView::SingleSelection);
        break;
    }

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
            this->setSelectionMode(QAbstractItemView::MultiSelection);
            this->selectAll();
        }
        break;
    }
    case Qt::Key_C:
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
        break;
    case Qt::Key_Backspace:
        emit eraseSignal();
        break;
    default:
    {
        break;
    }
    }

}

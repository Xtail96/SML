#include "smllistwidget.h"

SMLListWidget::SMLListWidget(QWidget *parent) :
    QListWidget(parent)
{

}

void SMLListWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    QListWidgetItem *selectedItem = this->currentItem();
    if(keyEvent->key() == Qt::Key_Return)
    {
        emit itemClicked(selectedItem);
    }
}

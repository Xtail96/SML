#include "sensorsdisplaywidget.h"

SensorsDisplayWidget::SensorsDisplayWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(0, 0, 0, 0);

    /*QLabel* titleLabel = new QLabel("Датчики", container);
    titleLabel->setAlignment(Qt::AlignCenter);
    container->layout()->addWidget(titleLabel);*/

    QTableWidget* sensorsTable = new QTableWidget(container);
    sensorsTable->setMaximumWidth(105);
    container->layout()->addWidget(sensorsTable);

    this->layout()->addWidget(container);
}

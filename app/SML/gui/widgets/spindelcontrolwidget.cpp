#include "spindelcontrolwidget.h"

SpindelControlWidget::SpindelControlWidget(QString spindelLabel, QString spindelName, size_t rotationsUpperBound, size_t rotationsLowerBound, size_t currentRotations, bool enable, QWidget *parent) :
    QWidget(parent),
    m_spindelLabel(spindelLabel),
    m_spindelName(spindelName),
    m_rotationsUpperBound(rotationsUpperBound),
    m_rotationsLowerBound(rotationsLowerBound),
    m_currentRotations(currentRotations),
    m_enable(enable)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(5, 5, 5, 5);

    QFrame* container = new QFrame(this);
    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    container->setLayout(containerLayout);
    //container->setStyleSheet("margin-left: 1px; margin-right: 1px; background-color: #eee; border: 1px solid #dfdfdf; border-radius: 5px;");
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(5, 5, 5, 5);

    // task title
    QLabel* titleLabel = new QLabel(m_spindelLabel, this);
    titleLabel->setStyleSheet("font-weight: bold; border: 1px solid transparent; background-color: transparent;");
    container->layout()->addWidget(titleLabel);

    QPushButton* enableButton = new QPushButton(container);
    if(!m_enable)
    {
        enableButton->setText("Включить");
    }
    else
    {
        enableButton->setText("Выключить");
    }
    container->layout()->addWidget(enableButton);

    this->layout()->addWidget(container);
}

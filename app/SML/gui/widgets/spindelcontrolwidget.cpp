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
    this->layout()->setContentsMargins(0, 5, 0, 5);

    QFrame* container = new QFrame(this);
    container->setLayout(new QVBoxLayout(container));
    //container->setStyleSheet("margin-left: 1px; margin-right: 1px; background-color: #eee; border: 1px solid #dfdfdf; border-radius: 5px;");
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(0, 0, 0, 0);

    QFrame* topFrame = new QFrame(container);
    topFrame->setLayout(new QHBoxLayout(topFrame));
    topFrame->layout()->setSpacing(0);
    topFrame->layout()->setContentsMargins(0, 0, 0, 0);
        QLabel* titleLabel = new QLabel(m_spindelLabel, container);
        titleLabel->setStyleSheet("font-weight: bold; border: 1px solid transparent; background-color: transparent;");
        topFrame->layout()->addWidget(titleLabel);

        QLCDNumber* rotationsDisplay = new QLCDNumber(container);
        rotationsDisplay->display(QString::number(m_currentRotations));
        rotationsDisplay->setSegmentStyle(QLCDNumber::Flat);
        rotationsDisplay->setFrameShape(QFrame::NoFrame);
        topFrame->layout()->addWidget(rotationsDisplay);
    container->layout()->addWidget(topFrame);



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

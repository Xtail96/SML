#include "spindel_control_widget.h"

SpindelControlWidget::SpindelControlWidget(QString spindelLabel, QString spindelName, QString spindelIndex, size_t rotationsUpperBound, size_t rotationsLowerBound, size_t currentRotations, bool enable, QWidget *parent) :
    QWidget(parent),
    m_spindelLabel(spindelLabel),
    m_spindelName(spindelName),
    m_spindelIndex(spindelIndex),
    m_rotationsUpperBound(rotationsUpperBound),
    m_rotationsLowerBound(rotationsLowerBound),
    m_currentRotations(currentRotations),
    m_enable(enable)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 1, 0, 1);

    QGroupBox* container = new QGroupBox(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(5, 5, 5, 5);

    QWidget* topContainerWidget = new QWidget(container);
    topContainerWidget->setLayout(new QHBoxLayout(topContainerWidget));
    topContainerWidget->layout()->setSpacing(0);
    topContainerWidget->layout()->setContentsMargins(0, 0, 0, 0);
        m_titleLabel = new QLabel(m_spindelLabel, container);
        m_titleLabel->setStyleSheet("font-weight: bold; border: 1px solid transparent; background-color: transparent;");
        topContainerWidget->layout()->addWidget(m_titleLabel);

        m_rotationsLCDNumber = new QLCDNumber(container);
        m_rotationsLCDNumber->display(QString::number(m_currentRotations));
        m_rotationsLCDNumber->setSegmentStyle(QLCDNumber::Flat);
        m_rotationsLCDNumber->setFrameShape(QFrame::NoFrame);
        topContainerWidget->layout()->addWidget(m_rotationsLCDNumber);
    container->layout()->addWidget(topContainerWidget);

    m_rotationsSlider = new QSlider(Qt::Horizontal, container);
    m_rotationsSlider->setMaximum(int(m_rotationsUpperBound));
    m_rotationsSlider->setMinimum(int(m_rotationsLowerBound));
    m_rotationsSlider->setValue(int(m_currentRotations));
    connect(m_rotationsSlider, SIGNAL(valueChanged(int)), this, SLOT(onRotationsSliderValueChanged(int)));
    container->layout()->addWidget(m_rotationsSlider);

    QWidget* buttonsContainerWidget = new QWidget(container);
    buttonsContainerWidget->setLayout(new QHBoxLayout(buttonsContainerWidget));
    //buttonsContainerWidget->layout()->setSpacing(1);
    buttonsContainerWidget->layout()->setContentsMargins(0, 0, 0, 0);
        m_switchPushButton = new QPushButton(buttonsContainerWidget);
        m_switchPushButton->setObjectName("switchPushButton");
        if(!m_enable)
        {
            m_switchPushButton->setText("Включить");
        }
        else
        {
            m_switchPushButton->setText("Выключить");
        }
        connect(m_switchPushButton, SIGNAL(clicked(bool)), this, SLOT(onSwitchSpindelClicked()));
        buttonsContainerWidget->layout()->addWidget(m_switchPushButton);

        m_warmingUpPushButton = new QPushButton("Прогреть", buttonsContainerWidget);
        connect(m_warmingUpPushButton, SIGNAL(clicked(bool)), this, SLOT(onWarmingSpindelUpClicked()));
        buttonsContainerWidget->layout()->addWidget(m_warmingUpPushButton);
    container->layout()->addWidget(buttonsContainerWidget);

    this->layout()->addWidget(container);
}

void SpindelControlWidget::onSwitchSpindelClicked()
{
    if(!m_enable)
    {
        emit switchOn(m_spindelIndex, m_currentRotations);
    }
    else
    {
        emit switchOff(m_spindelIndex);
    }
}

void SpindelControlWidget::onWarmingSpindelUpClicked()
{
    emit switchOn(m_spindelIndex, m_rotationsLowerBound);
}

void SpindelControlWidget::onRotationsSliderValueChanged(int value)
{
    m_currentRotations = size_t(value);
    m_rotationsLCDNumber->display(QString::number(m_currentRotations));
}

void SpindelControlWidget::updateControls(bool enable, size_t rotations)
{
    m_enable = enable;
    if(!m_enable)
    {
        //m_switchPushButton->setStyleSheet("");
        m_switchPushButton->setText("Включить");
        m_rotationsSlider->setEnabled(true);
    }
    else
    {
        //m_switchPushButton->setStyleSheet("background-color:#b22222; color: #fff;");
        m_currentRotations = rotations;
        m_switchPushButton->setText("Выключить");
        m_rotationsSlider->setEnabled(false);
        m_rotationsSlider->setValue(int(m_currentRotations));
        m_rotationsLCDNumber->display(QString::number(m_currentRotations));
    }
}

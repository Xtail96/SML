#include "sensors_display_widget.h"

SensorsDisplayWidget::SensorsDisplayWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    this->layout()->setContentsMargins(0, 0, 0, 5);

    QWidget* container = new QWidget(this);
    container->setLayout(new QVBoxLayout(container));
    container->layout()->setSpacing(0);
    container->layout()->setContentsMargins(0, 0, 0, 0);

    m_sensorsTable = new QTableWidget(container);
#ifdef Q_OS_MACOS
    m_sensorsTable->setMinimumWidth(110);
    m_sensorsTable->setMaximumWidth(110);
#endif
#ifdef Q_OS_LINUX
    m_sensorsTable->setMinimumWidth(150);
    m_sensorsTable->setMaximumWidth(150);
#endif
#ifdef Q_OS_WIN
    m_sensorsTable->setMinimumWidth(150);
    m_sensorsTable->setMaximumWidth(150);
#endif

    m_sensorsTable->setLayoutDirection(Qt::RightToLeft);
    m_sensorsTable->setShowGrid(true);
    //m_sensorsTable->

    container->layout()->addWidget(m_sensorsTable);

    this->layout()->addWidget(container);
}

void SensorsDisplayWidget::update()
{
    m_sensorsTable->clear();

    QStringList labels;
    QList<QTableWidgetItem*> items;
    for(auto sensor : m_sensors)
    {
        labels.push_back(sensor->label);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackgroundColor(sensor->led);
        item->setFlags(Qt::ItemIsEnabled);
        items.push_back(item);
    }

    m_sensorsTable->setColumnCount(1);
    m_sensorsTable->setRowCount(labels.size());
    m_sensorsTable->setVerticalHeaderLabels(labels);

    QHeaderView*horizontalHeader = m_sensorsTable->horizontalHeader();
    horizontalHeader->setVisible(false);
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    QHeaderView* verticalHeader = m_sensorsTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(25);

    for(int i = 0; i < items.size(); i++)
    {
        m_sensorsTable->setItem(i, 0, items[i]);
    }
}

void SensorsDisplayWidget::addSensor(QString name, QString label, QColor led)
{
    m_sensors.push_back(QSharedPointer<SensorWidget>(new SensorWidget(name, label, led)));
    this->update();
}

void SensorsDisplayWidget::removeSensor(QString name)
{
    try
    {
        m_sensors.removeAll(findSensor(name));
        this->update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

void SensorsDisplayWidget::updateSensorState(QString name, QColor led)
{
    try
    {
        this->findSensor(name)->led = led;
        this->update();
    }
    catch(std::invalid_argument e)
    {
        QMessageBox(QMessageBox::Warning, "SensorDisplayWidget error", e.what());
    }
}

QSharedPointer<SensorsDisplayWidget::SensorWidget> SensorsDisplayWidget::findSensor(QString name)
{
    for(auto sensor : m_sensors)
    {
        if(sensor->name == name)
        {
            return sensor;
        }
    }

    throw std::invalid_argument("can not find sensor with name" + name.toStdString());
}
